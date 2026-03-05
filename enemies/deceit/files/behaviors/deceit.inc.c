
// Create a hitbox and an attack handler to damage Mario

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

// This controls the transparency of the light beam material
Gfx *deceit_light_proximity(s32 callContext, UNUSED struct GraphNode *node) {
    struct Object *curObj;
    Gfx *dlStart, *dlHead;
    struct GraphNodeGenerated *currentGraphNode = (struct  GraphNodeGenerated *) node;
    

    if (callContext == GEO_CONTEXT_RENDER) { // Called every frame the object is on screen
        curObj = (struct Object *) gCurGraphNodeObject;
        dlStart = alloc_display_list(sizeof(Gfx) * 2);
        dlHead = dlStart;

        f32 dist = curObj->oDistanceToMario - 600;
        dist = MIN(MAX(dist, 0), 255);

        gDPSetPrimColor(dlHead++, 0, 0, 255, 255, 255, dist); // Sets alpha based on Mario's distance to the object
        gSPEndDisplayList(dlHead);

        currentGraphNode->fnNode.node.flags |= (LAYER_TRANSPARENT << 8); // assign to transparent layer
    }
    return dlStart;
}

// idle state
void deceit_sleep(void) {
    
    // do the almost non perceptible sleep animation
    cur_obj_init_animation(0);
    if (o->oDistanceToMario < 500) { // If Mario is close, chase him !
        o->oAction = 1; // Switch to chgase mode !
    }
    
    o->oForwardVel = approach_f32(o->oForwardVel, 0.0f, 0x2, 0x2); // Decrease velocity until 0 because the deceit is idle

}

void deceit_attack(void) {

    // set chase animation a little bit sped up
    cur_obj_init_animation_with_accel_and_sound(1, 1.5);
    if (o->oDistanceToMario > 1200) { // If Mario is too far, sleep again
        if (cur_obj_check_if_at_animation_end()) {
            o->oAction = 0; // Switch to Sleep state once the animation is done
        }
    }

    o->oForwardVel = approach_f32(o->oForwardVel, 9.5f, 0.8, 0.8); // Increase velocity until 9.5 because the deceit is chasing Mario

    // Face toward Mario
    o->oDeceitTargetDirection = o->oAngleToMario;
    cur_obj_rotate_yaw_toward(o->oDeceitTargetDirection, 0xC0);
    
    // Everytime the deceit's chase animation starts/loops and if it's on the ground, jump !
    if (cur_obj_init_anim_check_frame(1, 1) && (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND)) {
        o->oVelY = 20;
    }
    
    // Everytime the deceit's chase animation reaches frame 18, play a chomping sound !
    if (cur_obj_init_anim_check_frame(1, 18)) {
        cur_obj_play_sound_2(SOUND_OBJ_MAD_PIANO_CHOMPING);
    }

}

// initiate the deceit
void deceit_init(void) {
    obj_set_hitbox(o, &sDeceitHitbox); // assign the hitbox we created
}

// this codes loops forever
void deceit_loop(void) {

    // Select what kind of code to execute
    switch (o->oAction) {
        case 0: // idle
            deceit_sleep();
        break;

        case 1: // chasing Mario
            deceit_attack();
        break;
    }
    
    // Makes it able to collide with floors, walls and other objects
    cur_obj_move_standard(78);
    cur_obj_update_floor_and_walls();
    obj_bounce_off_walls_edges_objects(&o->oDeceitTargetDirection);

    obj_handle_attacks(&sDeceitHitbox, o->oAction, sDeceitAttackHandlers); // assign the attack handler we created every frame

}
