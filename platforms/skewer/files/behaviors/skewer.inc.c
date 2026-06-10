
// bunch of values that never changes
f32 skewer_hit_range = 250;
f32 skewer_length = 2700;
f32 skewer_damage = 2;
f32 skewer_retract_speed = 0.025;
f32 skewer_pre_launch_speed = 0.018;
f32 skewer_extend_speed = 0.05;

// Returns a float between 0.0f and 1.0f that represents what section of the line was projected to. (0.0 = at point1, 1.0 = at point2, 0.5 = middle)
f32 vec3f_project_to_line_skewer(Vec3f dest, Vec3f point, Vec3f point1, Vec3f point2) {
    //project mario's position to the line segment between p1 and p2
    Vec3f AB;
    Vec3f AP;

    vec3f_diff(AB,point2,point1);
    vec3f_diff(AP,point,point1);

    f32 AB_length_squared = vec3f_dot(AB,AB);

    f32 t = vec3f_dot(AP,AB) / AB_length_squared;
    if (t > 1.0f) {
        t = 1.0f;
    }
    if (t < 0.0f) {
        t = 0.0f;
    }

    Vec3f closestPoint;
    vec3f_copy(closestPoint,AB);
    vec3_scale(closestPoint,t);
    vec3f_sum(closestPoint,point1,closestPoint);

    vec3f_copy(dest,closestPoint);

    return t;
}
// The chunk of code above was provided by Rovert, thank you !

// spawn the collumn
void skewer_base_init (void) {
    spawn_object(o, MODEL_SKEWER, bhvSkewer);
}

// math to find the endpoint of the skewer no matter how its oriented !
void find_skewer_end_point(f32 x, f32 y, f32 z, Vec3f vector) {

    // Rotate around Z-axis (roll)
    f32 x_roll = x * coss(o->oFaceAngleRoll) - y * sins(o->oFaceAngleRoll);
    f32 y_roll = x * sins(o->oFaceAngleRoll) + y * coss(o->oFaceAngleRoll);
    f32 z_roll = z;

    // Rotate around X-axis (pitch
    f32 x_pitch = x_roll;
    f32 y_pitch = y_roll * coss(o->oFaceAnglePitch) - z_roll * sins(o->oFaceAnglePitch);
    f32 z_pitch = y_roll * sins(o->oFaceAnglePitch) + z_roll * coss(o->oFaceAnglePitch);

    // Rotate around Y-axis (yaw)
    f32 x_yaw = x_pitch * coss(o->oFaceAngleYaw) + z_pitch * sins(o->oFaceAngleYaw);
    f32 y_yaw = y_pitch;
    f32 z_yaw = -x_pitch * sins(o->oFaceAngleYaw) + z_pitch * coss(o->oFaceAngleYaw);

    vector[0] = o->oPosX + x_yaw;
    vector[1] = o->oPosY + y_yaw;
    vector[2] = o->oPosZ + z_yaw;
}

// set default values
void skewer_init(void) {
    
    Vec3f skewer_retract_pos_init; // sets the location for where the skewer will retract to after extending !
    find_skewer_end_point(0, -skewer_length + 150, 0, skewer_retract_pos_init);
    o->oSkewerRetractPosX = skewer_retract_pos_init[0];
    o->oSkewerRetractPosY = skewer_retract_pos_init[1];
    o->oSkewerRetractPosZ = skewer_retract_pos_init[2];
    
    Vec3f skewer_pre_launch_pos_init; // sets the location for where the skewer will retract to before extending !
    find_skewer_end_point(0, -skewer_length, 0, skewer_pre_launch_pos_init);
    o->oSkewerPreLaunchPosX = skewer_pre_launch_pos_init[0];
    o->oSkewerPreLaunchPosY = skewer_pre_launch_pos_init[1];
    o->oSkewerPreLaunchPosZ = skewer_pre_launch_pos_init[2];

}

// Core loop, happens every frame !
void skewer_loop(void) {

    Vec3f skewer_top_pos; // find the top of the skewer every frame to update the collision distance (we dont want to damage Mario where the collumn was when it was extended instead of where the skewer currently is !)
    find_skewer_end_point(0, skewer_length, 0, skewer_top_pos);
    
    // assign the values we gathered earlier
    Vec3f skewer_retract_pos;
    skewer_retract_pos[0] = o->oSkewerRetractPosX;
    skewer_retract_pos[1] = o->oSkewerRetractPosY;
    skewer_retract_pos[2] = o->oSkewerRetractPosZ;
    
    Vec3f skewer_pre_launch_pos;
    skewer_pre_launch_pos[0] = o->oSkewerPreLaunchPosX;
    skewer_pre_launch_pos[1] = o->oSkewerPreLaunchPosY;
    skewer_pre_launch_pos[2] = o->oSkewerPreLaunchPosZ;
    
    Vec3f skewer_extend_pos;
    skewer_extend_pos[0] = o->oHomeX;
    skewer_extend_pos[1] = o->oHomeY;
    skewer_extend_pos[2] = o->oHomeZ;


    // How does this thing work ? Well we trace a line from the bottom of the skewer to the top of it.
    // Then we say "If Mario is close enough to this invisible line that goes through the collumn, damage Mario !"
    // The invisible line moves along with the collumn as it moves
    Vec3f closest_skewer_pos;
    Vec3f skewer_pos = { o->oPosX, o->oPosY, o->oPosZ };
    vec3f_project_to_line_skewer(closest_skewer_pos, gMarioState->pos, skewer_pos, skewer_top_pos);
    f32 distance_from_skewer;
    vec3_get_dist(closest_skewer_pos, gMarioState->pos, &distance_from_skewer);
    
    if (distance_from_skewer < skewer_hit_range) {
        spawn_object(o, MODEL_NONE, bhvSkewerDamage);
    }
    

    // states of the skewer !
    // Pretty self expanatory, we interpolate the position of where it is and where we want it to go !
    // We use animations for the twirling so we don't have to mess with rotation matrices to account for every orientation the skewer can be in :)
    switch (o->oAction) {    
        case SKEWER_RETRACT:
            approach_vec3f_asymptotic(skewer_pos, skewer_pre_launch_pos, skewer_retract_speed, skewer_retract_speed, skewer_retract_speed);
            cur_obj_init_animation_and_extend_if_at_end(0);

            Vec3f skewer_dist_from_retract_pos_vec;
            vec3_diff(skewer_dist_from_retract_pos_vec, skewer_pos, skewer_retract_pos);
            f32 skewer_dist_from_retract_pos_dist = vec3_mag(skewer_dist_from_retract_pos_vec);
            if (skewer_dist_from_retract_pos_dist < 100) {
                o->oAction = SKEWER_IDLE;
            }

        break;

        case SKEWER_IDLE:
            if (cur_obj_check_if_near_animation_end()) {
                cur_obj_init_animation_and_extend_if_at_end(1);
            }
            o->oSkewerIdleTimer += 1;
            if (o->oSkewerIdleTimer >= 90) {
                o->oSkewerIdleTimer = 0;
                o->oAction = SKEWER_PRE_LAUNCH;
            }
            break;
    
        case SKEWER_PRE_LAUNCH:
            approach_vec3f_asymptotic(skewer_pos, skewer_retract_pos, skewer_pre_launch_speed, skewer_pre_launch_speed, skewer_pre_launch_speed);
            cur_obj_init_animation_and_extend_if_at_end(2);

            Vec3f skewer_dist_from_pre_launch_pos_vec;
            vec3_diff(skewer_dist_from_pre_launch_pos_vec, skewer_pos, skewer_retract_pos);
            f32 skewer_dist_from_pre_launch_pos_dist = vec3_mag(skewer_dist_from_pre_launch_pos_vec);
            if (skewer_dist_from_pre_launch_pos_dist < 10) {
                o->oAction = SKEWER_EXTEND;
            }
        break;

        case SKEWER_EXTEND:
            approach_vec3f_asymptotic(skewer_pos, skewer_extend_pos, skewer_extend_speed, skewer_extend_speed, skewer_extend_speed);
            cur_obj_init_animation_and_extend_if_at_end(3);

            Vec3f skewer_dist_from_extend_pos_vec;
            vec3_diff(skewer_dist_from_extend_pos_vec, skewer_pos, skewer_extend_pos);
            f32 skewer_dist_from_extend_pos_dist = vec3_mag(skewer_dist_from_extend_pos_vec);
            if (skewer_dist_from_extend_pos_dist < 100) {
                o->oAction = SKEWER_IDLE_EXTENDED;
            }

        break;

        case SKEWER_IDLE_EXTENDED:
            if (cur_obj_check_if_near_animation_end()) {
                cur_obj_init_animation_and_extend_if_at_end(1);
            }
            o->oSkewerIdleTimer += 1;
            if (o->oSkewerIdleTimer >= 90) {
                o->oSkewerIdleTimer = 0;
                o->oAction = SKEWER_RETRACT;
            }
            
        break;
    }

    // assign the interpolated positions to the real object's positions
    o->oPosX = skewer_pos[0];
    o->oPosY = skewer_pos[1];
    o->oPosZ = skewer_pos[2];

}



// VERY hacky way of dealing damage to Mario, basically "spawn an invisible enemy on top of Mario then delete it"
static struct ObjectHitbox sSkewerDamageHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 0,
    /* height:            */ 0,
    /* hurtboxRadius:     */ 300,
    /* hurtboxHeight:     */ 300,
};

static u8 sSkewerDamageAttackHandlers[] = {

    /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_NOP,
    /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_NOP,
    /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_NOP,
    /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_NOP,
    /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_NOP,
    /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_NOP,
};

void skewer_damage_init(void) {
    obj_set_hitbox(o, &sSkewerDamageHitbox);
    o->oPosX = gMarioState->pos[0];
    o->oPosY = gMarioState->pos[1] + 500;
    o->oPosZ = gMarioState->pos[2];
    o->oSkewerDamageTimer = 30;
}

void skewer_damage_loop(void) {
    o->oPosX = gMarioState->pos[0];
    o->oPosY = gMarioState->pos[1];
    o->oPosZ = gMarioState->pos[2];
    obj_handle_attacks(&sSkewerDamageHitbox, 0, sSkewerDamageAttackHandlers);
    o->oSkewerDamageTimer -= 1;
    if (o->oSkewerDamageTimer <= 0) {
        obj_mark_for_deletion(o);
    }
}
