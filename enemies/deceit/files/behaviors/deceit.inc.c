static struct ObjectHitbox sDeceitHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 90,
    /* height:            */ 170,
    /* hurtboxRadius:     */ 80,
    /* hurtboxHeight:     */ 160,
};

static u8 sDeceitAttackHandlers[] = {
    /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_NOP,
    /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_NOP,
    /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_NOP,
    /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_NOP,
    /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_NOP,
    /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_NOP,
};

Gfx *deceit_light_proximity(s32 callContext, UNUSED struct GraphNode *node) {
    struct Object *curObj;
    Gfx *dlStart, *dlHead;
    struct GraphNodeGenerated *currentGraphNode = (struct  GraphNodeGenerated *) node;
    

    if (callContext == GEO_CONTEXT_RENDER) {
        curObj = (struct Object *) gCurGraphNodeObject;
        dlStart = alloc_display_list(sizeof(Gfx) * 2);
        dlHead = dlStart;

        f32 dist = curObj->oDistanceToMario - 600;
        dist = MIN(MAX(dist, 0), 255);

        gDPSetPrimColor(dlHead++, 0, 0, 255, 255, 255, dist);
        gSPEndDisplayList(dlHead);

        currentGraphNode->fnNode.node.flags |= (LAYER_TRANSPARENT << 8);
    }
    return dlStart;
}

void deceit_sleep(void) {
    
    cur_obj_init_animation(0);
    if (o->oDistanceToMario < 500) {
        o->oAction = 1;
    }
    
    o->oForwardVel = approach_f32(o->oForwardVel, 0.0f, 0x2, 0x2);

}

void deceit_attack(void) {

    cur_obj_init_animation_with_accel_and_sound(1, 1.5);
    if (o->oDistanceToMario > 1200) {
        if (cur_obj_check_if_at_animation_end()) {
            o->oAction = 0;
        }
    }

    o->oForwardVel = approach_f32(o->oForwardVel, 9.5f, 0.8, 0.8);

    o->oDeceitTargetDirection = o->oAngleToMario;

    cur_obj_rotate_yaw_toward(o->oDeceitTargetDirection, 0xC0);
    
    if (cur_obj_init_anim_check_frame(1, 1) && (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND)) {
        o->oVelY = 20;
    }
    
    if (cur_obj_init_anim_check_frame(1, 18)) {
        cur_obj_play_sound_2(SOUND_OBJ_MAD_PIANO_CHOMPING);
    }

}

void deceit_init(void) {
    obj_set_hitbox(o, &sDeceitHitbox);
}

void deceit_loop(void) {

    switch (o->oAction) {
        case 0:
            deceit_sleep();
        break;

        case 1:
            deceit_attack();
        break;
    }
    
    cur_obj_move_standard(78);
    cur_obj_update_floor_and_walls();
    obj_bounce_off_walls_edges_objects(&o->oDeceitTargetDirection);

    obj_handle_attacks(&sDeceitHitbox, o->oAction, sDeceitAttackHandlers);

}