
// Create a hitbox and an attack handler to damage Mario and be damaged

static struct ObjectHitbox sBomboomBombHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 30,
    /* height:            */ 30,
    /* hurtboxRadius:     */ 30,
    /* hurtboxHeight:     */ 30,
};

static u8 sBomboomBombAttackHandlers[] = {
    /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_NOP,
    /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_NOP,
    /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_NOP,
    /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_NOP,
    /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_NOP,
    /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_NOP,
};

// This sets the bomb's color !
Gfx *bomboom_bomb_color(s32 callContext, UNUSED struct GraphNode *node) {
    struct Object *curObj;
    Gfx *dlStart, *dlHead;
    struct GraphNodeGenerated *currentGraphNode = (struct  GraphNodeGenerated *) node;
    

    if (callContext == GEO_CONTEXT_RENDER) { // Called every frame the object is on screen
        curObj = (struct Object *) gCurGraphNodeObject;
        dlStart = alloc_display_list(sizeof(Gfx) * 2);
        dlHead = dlStart;

        curObj->oBomboomBombCurrentColor = approach_s32(curObj->oBomboomBombCurrentColor, curObj->oBomboomBombTargetColor, 25, 25); // interpolate between colors Black and Red
        
        gDPSetPrimColor(dlHead++, 0, 0, 255, 255, 255, curObj->oBomboomBombCurrentColor); // Assign the color
        gSPEndDisplayList(dlHead);

        currentGraphNode->fnNode.node.flags |= (LAYER_OPAQUE << 8); // Assign to Opaque draw layer !
    }
    return dlStart;
}

// initiate the actor and set default values
void bomboom_bomb_init(void) {
    o->oBomboomBombTimer = 0;
    o->oBomboomBombTargetColor = 255;
    o->oBomboomBombCurrentColor = 255;
    o->oBomboomBombSpeed = random_float() + 0.2;
    o->oForwardVel = o->oBomboomBombSpeed * 35;
    cur_obj_play_sound_2(SOUND_AIR_BOBOMB_LIT_FUSE);
}

// this codes loops forever
void bomboom_bomb_loop(void) {

    // Select what kind of code to execute
    switch (o->oAction) {
        case 0: // init
            // Handle color switching
            if (o->oBomboomBombTimer >= 70) {
                if ((o->oBomboomBombColorTimer > 18)) {
                    if (o->oBomboomBombTargetColor == 255) {o->oBomboomBombTargetColor = 0;}
                    else {o->oBomboomBombTargetColor = 255;}
                    o->oBomboomBombColorTimer = 0;
                }
            }

            if ((o->oBomboomBombTimer >= 140) || (o->oDistanceToMario < 30)) {
                o->oAction = 1; // Explode the bomb if too close to Mario or if the fuze time is up !!
            }
        break;

        case 1: // Explode, boom ! :D
            cur_obj_play_sound_1(SOUND_GENERAL2_BOBOMB_EXPLOSION); // play sound
            obj_mark_for_deletion(o);
        break;
    }

    if (obj_handle_attacks(&sBomboomBombHitbox, o->oAction, sBomboomBombAttackHandlers)) { // assign the attack handler we created every frame
        o->oBomboomBombTimer = 150; // Explode the bomb if too close to Mario !
    }
    
    o->oBomboomBombTimer += 1;
    o->oBomboomBombColorTimer += 1;

    o->oForwardVel = approach_f32(o->oForwardVel, 0.1, 0.15, 0.15);
    o->oMoveAngleYaw = approach_f32(o->oMoveAngleYaw, o->oAngleToMario, o->oForwardVel * 35, o->oForwardVel * 35);
    cur_obj_init_animation_with_accel_and_sound(0, o->oForwardVel * 4 / 25);
    
    cur_obj_move_standard(78);
    cur_obj_update_floor_and_walls();
    obj_bounce_off_walls_edges_objects(&o->oMoveAngleYaw);
}

// idle state
void bomboom_sleep(void) {
    if (o->oDistanceToMario < 1500) {
        o->oAction = 1; // If Mario is close enough, switch to attack mode !
    }
    
}

// Attack Mario !
void bomboom_attack(void) {
    if (o->oDistanceToMario >= 2000) {
        o->oAction = 0; // If Mario is too far, go idle
    }

    // Move forward or backward depending on Mario's distance !
    if (o->oDistanceToMario > 800) {
        o->oForwardVel = approach_f32(o->oForwardVel, 4, 0.2, 0.2);
    } else if (o->oDistanceToMario < 700) {
        o->oForwardVel = approach_f32(o->oForwardVel, -4, 0.2, 0.2);
    } else {
        o->oForwardVel = approach_f32(o->oForwardVel, 0, 0.2, 0.2);
    }

    // Launche a bomb every 40 frames !
    if (o->oBomboomTimer >= 40) {
        o->oBomboomTimer = 0;
        spawn_object(o, MODEL_BOMBOOM_BOMB, bhvBomboomBomb);
        cur_obj_play_sound_1(SOUND_OBJ_CANNON_BARREL_PITCH);
    }
    o->oBomboomTimer += 1;
    
    // rotate toward Mario !
    o->oMoveAngleYaw = approach_f32(o->oMoveAngleYaw, o->oAngleToMario, 300, 300);

}

// initiate the actor and set default values
void bomboom_init(void) {
    o->oBomboomTimer = 0;
}

// this codes loops forever
void bomboom_loop(void) {

    // Select what kind of code to execute
    switch (o->oAction) {
        case 0: // he sleepy :3
            bomboom_sleep();
        break;

        case 1: // attack
            bomboom_attack();
        break;

        case 2: // dead !
            cur_obj_play_sound_1(SOUND_GENERAL2_BOBOMB_EXPLOSION);

            spawn_object_relative(0, 0, 150, -20, o, MODEL_YELLOW_COIN, bhvSingleCoinGetsSpawned);
            spawn_object_relative(0, -20, 150, 20, o, MODEL_YELLOW_COIN, bhvSingleCoinGetsSpawned);
            spawn_object_relative(0, 20, 150, 20, o, MODEL_YELLOW_COIN, bhvSingleCoinGetsSpawned);

            spawn_object_relative(0, 0, 30, 0, o, MODEL_EXPLOSION, bhvBobombFuseSmoke);

            obj_mark_for_deletion(o);
        break;
    }

    if (cur_obj_is_mario_ground_pounding_platform()) { // If Mario groundpounds the actor, mark as dead!
        o->oAction = 2;
    }
    
    // Makes it able to collide with floors, walls and other objects
    cur_obj_move_standard(78);
    cur_obj_update_floor_and_walls();
    obj_bounce_off_walls_edges_objects(&o->oMoveAngleYaw);

}
