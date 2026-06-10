
// Hitbox to detect when the block shall break !
struct ObjectHitbox sQuestionBlockHitbox = {
    .interactType      = INTERACT_BREAKABLE,
    .downOffset        = 10,
    .damageOrCoinValue = 0,
    .health            = 1,
    .numLootCoins      = 0,
    .radius            = 150,
    .height            = 260,
    .hurtboxRadius     = 0,
    .hurtboxHeight     = 0,
};

// struct defining the content of one box
struct QuestionBlockContents {
    ModelID32 model;
    const BehaviorScript *behavior;
    u8 behParam;
};

// Bunch of placeholders, if you run out of them just write new ones ! :D
enum QuestionBlockContentsList {
    LOLA_CUSTOM_ITEM_01,
    LOLA_CUSTOM_ITEM_02,
    LOLA_CUSTOM_ITEM_03,
    LOLA_CUSTOM_ITEM_04,
    LOLA_CUSTOM_ITEM_05,
    LOLA_CUSTOM_ITEM_06,
    LOLA_CUSTOM_ITEM_07,
    LOLA_CUSTOM_ITEM_08,
    LOLA_CUSTOM_ITEM_09,
    LOLA_CUSTOM_ITEM_10,
    LOLA_CUSTOM_ITEM_11,
    LOLA_CUSTOM_ITEM_12,
    LOLA_CUSTOM_ITEM_13,
    LOLA_CUSTOM_ITEM_14,
    LOLA_CUSTOM_ITEM_15,
    // Add more if you want ! :D
};

// The good stuff ! Here you decide what kind of goodies the box will have !
struct QuestionBlockContents sQuestionBlockContents[] = { // First object will spawn if the box has a first behavior parameter of 0x0, then 0x1 for the second etc !
    [LOLA_CUSTOM_ITEM_01        ] = { MODEL_CHUCKYA,  bhvChuckya,               0 }, // 0x0
    [LOLA_CUSTOM_ITEM_02        ] = { MODEL_AMP,  bhvCirclingAmp,               0 }, // 0x1 etc !
};

// spawn the item out of the box !
void question_block_spawn_contents(struct QuestionBlockContents *contentsList, u8 goodie) {
    struct Object *contentsObj = NULL;

    if (goodie < ARRAY_COUNT(sQuestionBlockContents)) {
        struct QuestionBlockContents *contents = &contentsList[goodie];

        contentsObj = spawn_object(o, contents->model, contents->behavior); // select object based off box's first behavior parameter !
        contentsObj->oVelY = random_u16() & 30; // set a random up velocity, max 30
        contentsObj->oForwardVel = (random_u16() & 5) * random_float(); // set a random forward velocity, from -5 to 5
        contentsObj->oMoveAngleYaw = random_u16(); // set a random yaw
        OR_BPARAM1(o->oBehParams, contents->behParam); // assign the parameter we chose in sQuestionBlockContents to the spawned actor ! :D
    }
}

// initialize the block and assign it's hitbox !
void question_block_init(void) {
    obj_set_hitbox(o, &sQuestionBlockHitbox);
}

// Core loop that will run every frame
void question_block_loop(void) {

    switch (o->oAction) { // idle
        case 0:
            if (cur_obj_was_attacked_or_ground_pounded()) {
                cur_obj_become_intangible();
                o->oAction = 1;
            }
            load_object_collision_model();
        break;
    
        case 1: // being destroyed
            question_block_spawn_contents(sQuestionBlockContents, o->oBehParams >> 24); // select object based off box's first behavior parameter !
            // spawn particles !
            spawn_mist_particles_variable(0, 0, 100.0f);
            spawn_triangle_break_particles(20, MODEL_CARTOON_STAR, 0.8f, o->oAnimState);
            // play a sound
            create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
            // delete the object :)
            obj_mark_for_deletion(o);
        break;
    }

    
}
