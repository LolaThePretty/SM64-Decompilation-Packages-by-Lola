
// Returns a float between 0.0f and 1.0f that represents what section of the line was projected to. (0.0 = at point1, 1.0 = at point2, 0.5 = middle)
f32 vec3f_project_to_line_melter(Vec3f dest, Vec3f point, Vec3f point1, Vec3f point2) {
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

// We use this to control the scale of the bone the flames are attached to in Blender ! (See blend file to understand further !)
Gfx *melter_flame_scale(s32 callContext, struct GraphNode *node) {
    struct Object *curObj;

    if (callContext == GEO_CONTEXT_RENDER) { // called every frame when the object is on screen
        curObj = (struct Object *) gCurGraphNodeObject; // our o object, important to do curObj-> instead of o-> here !
        
        ((struct GraphNodeScale *) node->next)->scale = curObj->oMelterFlameScale; // sets scale
    }
    return NULL;
}

// math to find the endpoint of the melter no matter how its oriented !
void find_melter_end_point(f32 x, f32 y, f32 z, Vec3f vector) {

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
void melter_init(void) {
    
    o->oMelterTimer = 0;
    if (o->oBehParams >> 24 == 0x1) { // if behavior param 1 is equal to 1, the melter will be running when the level start
        o->oMelterState = TRUE;
        o->oMelterFlameScale = 1;
    } else { // otherwise it will be extinguished at first, allowing it to light up when the other is not active, and vice versa !
        o->oMelterState = FALSE;
        o->oMelterFlameScale = 0;
    }

}


// Core loop, happens every frame !
void melter_loop(void) {

    if (o->oMelterState) {
        o->oMelterFlameScale = approach_f32(o->oMelterFlameScale, 1, 0.1, 0.1); // Interpolate scale to 1 !

        // How does this thing work ? Well we trace a line from the bottom of the melter to the top of it.
        // Then we say "If Mario is close enough to this invisible line that goes through the flame, damage Mario !"
        Vec3f closest_melter_pos;
        Vec3f melter_top_pos;
        Vec3f melter_pos = { o->oPosX, o->oPosY, o->oPosZ };
        find_melter_end_point(0, 800, 0, melter_top_pos);
        vec3f_project_to_line_melter(closest_melter_pos, gMarioState->pos, melter_pos, melter_top_pos);
        f32 distance_from_melter;
        vec3_get_dist(closest_melter_pos, gMarioState->pos, &distance_from_melter);

        if (distance_from_melter < 125) {
            spawn_object(o, MODEL_NONE, bhvMelterFlame);
        }
    } else {
        o->oMelterFlameScale = approach_f32(o->oMelterFlameScale, 0, 0.1, 0.1); // Interpolate scale to 0
    }

    // timer :)
    if (o->oMelterTimer >= 150) {
        o->oMelterState = !o->oMelterState;
        o->oMelterTimer = 0;
    }

    o->oMelterTimer += 1;

}

// VERY hacky way of dealing damage to Mario, basically "spawn an invisible enemy on top of Mario then delete it"
static struct ObjectHitbox sMelterDamageHitbox = {
    /* interactType:      */ INTERACT_FLAME,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 0,
    /* height:            */ 0,
    /* hurtboxRadius:     */ 300,
    /* hurtboxHeight:     */ 300,
};

static u8 sMelterDamageAttackHandlers[] = {

    /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_NOP,
    /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_NOP,
    /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_NOP,
    /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_NOP,
    /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_NOP,
    /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_NOP,
};


void melter_flame_init(void) {
    obj_set_hitbox(o, &sMelterDamageHitbox);
    o->oPosX = gMarioState->pos[0];
    o->oPosY = gMarioState->pos[1] - 500;
    o->oPosZ = gMarioState->pos[2];
    o->oMelterDamageTimer = 30;
}

void melter_flame_loop(void) {
    o->oPosX = gMarioState->pos[0];
    o->oPosY = gMarioState->pos[1];
    o->oPosZ = gMarioState->pos[2];
    obj_handle_attacks(&sMelterDamageHitbox, 0, sMelterDamageAttackHandlers);
    o->oMelterDamageTimer -= 1;
    if (o->oMelterDamageTimer <= 0) {
        obj_mark_for_deletion(o);
    }
}
