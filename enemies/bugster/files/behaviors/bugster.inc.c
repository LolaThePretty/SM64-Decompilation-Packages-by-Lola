Bool32 bugsterDead = FALSE;

static struct ObjectHitbox sBugsterHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 40,
    /* height:            */ 30,
    /* hurtboxRadius:     */ 23,
    /* hurtboxHeight:     */ 5,
};

static u8 sBugsterAttackHandlers[] = {
    /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_SQUISHED,
    /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_SQUISHED,
    /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_KNOCKBACK,
};

void act_bugster_idle(void) {
    cur_obj_init_animation_with_accel_and_sound(0, 1);

    o->oForwardVel = approach_f32(o->oForwardVel, 0.0f, 0x6, 0x6);

    if (o->oBugsterActionTimer > 30) {
        o->oAction = 1;
        o->oBugsterActionTimer = 0;
    }
    

}

void act_bugster_walk(void) {
    cur_obj_init_animation_with_accel_and_sound(1, 2);

    o->oForwardVel = approach_f32(o->oForwardVel, 5.0f, 0x6, 0x6);

    if (o->oDistanceToMario > 1000) {
        f32 threshold = 1000;
        Vec3f d;
        if (o->oBugsterIsLeader == 1) {
            threshold = 1000;
            vec3f_diff(d, &o->oHomeVec, &o->oPosVec);

            if (vec3_sumsq(d) > sqr(threshold)) {
                o->oAngleToHome = atan2s(d[2], d[0]);
                cur_obj_rotate_yaw_toward(o->oAngleToHome, 0xFFF);
            }
        } else {
            threshold = 150;
            vec3f_diff(d, &o->oBugsterLeaderActor->oPosVec, &o->oPosVec);

            if (vec3_sumsq(d) > sqr(threshold)) {
                o->oAngleToHome = atan2s(d[2], d[0]);
                cur_obj_rotate_yaw_toward(o->oAngleToHome, 0xFFF);
            }
        }

        if (o->oBugsterActionTimer > 60) {
            o->oAction = 0;
            o->oBugsterActionTimer = 0;
        }
    } else {
        cur_obj_rotate_yaw_toward(o->oAngleToMario, 0xFFF);
    }

    if (o->oBugsterDirectionTimer > 15) {
        o->oBugsterDirectionTimer = 0;
        o->oBugsterTargetDirection = obj_random_fixed_turn(0x4000);
    }

    cur_obj_rotate_yaw_toward(o->oBugsterTargetDirection, 0x60);



}

void bugster_leader_init(void) {
    o->oBugsterActionTimer = 0;
    o->oBugsterDirectionTimer = 0;
    o->oBugsterTargetDirection = 0;
    o->oBugsterIsLeader = 1;
    o->oBugsterLeaderActor = NULL;
    
    int i;
    for (i = 0; i < (random_u16() & 3) + 1; i++) {
        spawn_object(o, MODEL_BUGSTER, bhvBugsterMinion);
    }
    
}

void bugster_minion_init(void) {
    o->oBugsterActionTimer = 0;
    o->oBugsterDirectionTimer = 0;
    o->oBugsterTargetDirection = 0;
    o->oBugsterIsLeader = 0;
    o->oBugsterLeaderActor = cur_obj_nearest_object_with_behavior(bhvBugsterLeader);
}

void bugster_loop(void) {

    switch (o->oAction) {

        case 0:
            act_bugster_idle();
        break;
        
        case 1:
            act_bugster_walk();
        break;

    }

    if (obj_handle_attacks(&sBugsterHitbox, o->oAction, sBugsterAttackHandlers) && !(bugsterDead)) {
        bugsterDead = TRUE;
    }

    if (bugsterDead) {
        
        obj_update_standard_actions(1);
    }

    cur_obj_move_standard(78);
    cur_obj_update_floor_and_walls();
    obj_bounce_off_walls_edges_objects(&o->oBugsterTargetDirection);

    o->oBugsterActionTimer += 1;
    o->oBugsterDirectionTimer += 1;

}