Bool32 croakDead = FALSE;

static struct ObjectHitbox sCroakHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 1,
    /* radius:            */ 90,
    /* height:            */ 70,
    /* hurtboxRadius:     */ 70,
    /* hurtboxHeight:     */ 60,
};

static u8 sCroakAttackHandlers[] = {
    /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_SQUISHED,
    /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_SQUISHED,
    /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_KNOCKBACK,
};

Gfx *croak_bubble(s32 callContext, struct GraphNode *node) {
    if (callContext == GEO_CONTEXT_RENDER) {
        o->oCroakBubbleTimer += 0.1f;
        f32 bubble_scale = absi(coss((o->oCroakBubbleTimer) * 4200) + 0.85);
        ((struct GraphNodeScale *) node->next)->scale = bubble_scale;
    }
    return NULL;
}


void croak_begin_jump(void) {
    o->oForwardVel = 0.0f;
    o->oVelY = 50.0f;
    o->oCroakCanJump = 0;
    cur_obj_play_sound_2(SOUND_GENERAL_CRAZY_BOX_BOING_FAST);
}

void croak_jump(void) {
    cur_obj_move_standard(-78);
    if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
        o->oAction = 0;
    }
}

void croak_check_for_mario_jump(void) {
    if ((o->oCroakCanJump == 1) && (o->oDistanceToMario < 600 && (gMarioState->action & ACT_JUMP))) {
        croak_begin_jump();
        cur_obj_init_animation_and_extend_if_at_end(2);
        o->oAction = 2;
    }
    
}

void croak_decide_next_move(void) {
    if (o->oCroakActionTimer >= 40) {
        f32 next_croak_action = random_sign();
        if (next_croak_action == -1) {
            o->oAction = 0;
        } else {
            o->oCroakDirectionTarget = obj_random_fixed_turn(0x2000);
            o->oAction = 1;
        }
        o->oCroakActionTimer = 0;
    }
}

void croak_idle(void) {

    cur_obj_init_animation_with_accel_and_sound(0, 1.0f);

    o->oForwardVel = approach_f32(o->oForwardVel, 0.0f, 0.03, 0.03);

    cur_obj_move_standard(-78);

    croak_check_for_mario_jump();

    croak_decide_next_move();

}

void croak_walk(void) {

    cur_obj_init_animation_with_accel_and_sound(1, 1.0f);

    o->oForwardVel = approach_f32(o->oForwardVel, 1.0f, 0.03, 0.03);
    cur_obj_rotate_yaw_toward(o->oCroakDirectionTarget, 0x300);

    cur_obj_move_standard(-78);

    croak_check_for_mario_jump();

    croak_decide_next_move();


}

void croak_init(void) {

o->oCroakBubbleTimer = 1.0f;
o->oCroakActionTimer = 0.0f;
o->oCroakJumpTimer = 0.0f;
o->oCroakDirectionTarget = 0.0f;
o->oCroakCanJump = 1;
o->oCroakSoundTimer = 0.0f;

}

void croak_loop(void) {
    switch (o->oAction) {
        case 0: // idle
            croak_idle();
        break;

        case 1: // walking
            croak_walk();
        break;

        case 2: // jumping
            croak_jump();
        break;

        case 3: // handle death animation
             // Needs to be called every frame, which is why it's not in the if statement below which only trigger once
        break;
    }

    if (obj_handle_attacks(&sCroakHitbox, o->oAction, sCroakAttackHandlers) && !(croakDead)) {
        croakDead = TRUE;
    }

    if (croakDead) {
        
        obj_update_standard_actions(1);
    }
    

    o->oCroakActionTimer += 1;
    o->oCroakSoundTimer += 1;

    if ((o->oCroakCanJump != 1)) {
        o->oCroakJumpTimer += 1;
        if (o->oCroakJumpTimer >= 70) {
            o->oCroakJumpTimer = 0;
            o->oCroakCanJump = 1;
        }
    }

    if (o->oCroakSoundTimer > random_float() * 100 + 250) {
        cur_obj_play_sound_2(SOUND_OBJ_MIPS_RABBIT);
        o->oCroakSoundTimer = 0;
    }

    cur_obj_update_floor_and_walls();
    
    
}