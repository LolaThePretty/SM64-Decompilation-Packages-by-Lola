
// our mesh switch bone in our SWITCH actor in blender
Gfx *block_swap_switch_func(s32 callContext, struct GraphNode *node) {
    struct GraphNodeSwitchCase *switchCase = (struct GraphNodeSwitchCase *) node; // our switch bone's state
    struct Object *curObj;
    curObj = (struct Object *) gCurGraphNodeObject; // our o object, important to do curObj-> instead of o-> here !
    

    if (callContext == GEO_CONTEXT_RENDER) { // called every frame when the object is on screen !
        if (curObj->oBlockSwapSwitchStateOn == TRUE) { // If the SWITCH actor should be On, switch to the On mesh, else the Off one
            switchCase->selectedCase = 1;
        } else {
            switchCase->selectedCase = 0;
        }
    }
    return NULL;
}

// our material switch bone in our BLOCK actor in blender
Gfx *block_swap_block_color_func(s32 callContext, struct GraphNode *node) {
    struct GraphNodeSwitchCase *switchCase = (struct GraphNodeSwitchCase *) node;
    struct Object *curObj;
    curObj = (struct Object *) gCurGraphNodeObject; // our o object, important to do curObj-> instead of o-> here !
    

    if (callContext == GEO_CONTEXT_RENDER) { // called every frame when the object is on screen !
        if (curObj->oBlockSwapBlockColorRed == TRUE) { // If the block should be red, switch to the red material, else the blue one
            switchCase->selectedCase = 1;
        } else {
            switchCase->selectedCase = 0;
        }
    }
    return NULL;
}

// our mesh switch bone in our BLOCK actor in blender
Gfx *block_swap_block_state_func(s32 callContext, struct GraphNode *node) {
    struct GraphNodeSwitchCase *switchCase = (struct GraphNodeSwitchCase *) node;
    struct Object *curObj;
    curObj = (struct Object *) gCurGraphNodeObject; // our o object, important to do curObj-> instead of o-> here !
    

    if (callContext == GEO_CONTEXT_RENDER) { // called every frame when the object is on screen !
        if (curObj->oBlockSwapBlockStateOn == TRUE) { // If the BLOCK actor should be On, switch to the On mesh, else the Off one
            switchCase->selectedCase = 1;
        } else {
            switchCase->selectedCase = 0;
        }
    }
    return NULL;
}

// initiate the platform and set default values of the switch
void block_swap_switch_init(void) {

    if (o->oBehParams2ndByte <= 1) { // If our second behavior parameter is more than 1, we set the switch to be Red, else Blue
        o->oBlockSwapSwitchStateOn = TRUE;
    } else {
        o->oBlockSwapSwitchStateOn = FALSE;
    }

    o->oBlockSwapSwitchIncrementTimer = FALSE;
    o->oBlockSwapSwitchTimer = 0;
}

// this code runs over and over forever
void block_swap_switch_loop(void) {
    // BIG if statement to detect if Mario is ground pounding it or if he is hitting the switch from below. If he does, do the following:
    if ((o->oBlockSwapSwitchTimer <= 0) && ((cur_obj_is_mario_ground_pounding_platform()) || (((gMarioObject->oVelY > 0 && o->oDistanceToMario < 300) && (gMarioState->action & ACT_FLAG_AIR)) && ((gMarioState->pos[1] < o->oPosY - 250) && ((gMarioState->pos[1] > o->oPosY - 300)))))) {
        o->oBlockSwapSwitchStateOn = !o->oBlockSwapSwitchStateOn; // Set the switch to the other state
        o->oBlockSwapSwitchIncrementTimer = TRUE; // allow a cooldown timer to increase
        o->oBlockSwapSwitchTimer = 10; // set the cooldown timer to 10 frames (otherwise the block would swap state over and over again every frame that mario hits it)
        play_sound(SOUND_GENERAL_SWITCH_DOOR_OPEN, gGlobalSoundSource); // play a sound
    }

    if (o->oBlockSwapSwitchIncrementTimer == TRUE) { // If we allow the cooldown timer to decrease, decrease it
        o->oBlockSwapSwitchTimer -= 1;
    }

    if (o->oBlockSwapSwitchTimer <= 0) { // If the cooldown timer reaches 0, dont allow it to decrease anymore
        o->oBlockSwapSwitchIncrementTimer = FALSE;
    }
    
    
    
}

// initiate the block and set default values
void block_swap_block_init(void) {

    o->oBlockSwapBlockAssignedSwitch = NULL; // failsafe to prevent the game from crashing, we set it to NULL and later check if it isn't NULL, otherwise do nothing

    // Here we are finding every single switch actors
    uintptr_t *behaviorAddr = segmented_to_virtual(bhvBlockSwapSwitch);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct ObjectNode *obj = listHead->next;

    while (listHead != obj) {
        if (((struct Object *) obj)->behavior == behaviorAddr) {
            // We look to see if they have the same first parameter as the block
            if ((((struct Object *) obj)->oBehParams >> 24) == (o->oBehParams >> 24)) {
                // If it does, assign this switch to this block and stop the loop ! Else continue to iterate through the switches until you find one that has the same first parameter as the block
                o->oBlockSwapBlockAssignedSwitch = (struct Object *) obj;
                break;
            }
        }
        obj = obj->next;
    }

    // If we didn't find any switch actor to assign, o->oBlockSwapBlockAssignedSwitch remains NULL

    if (o->oBehParams2ndByte <= 1) { // If our second behavior parameter is more than 1, we set the block to be Red, else Blue
        o->oBlockSwapBlockColorRed = TRUE;
    } else {
        o->oBlockSwapBlockColorRed = FALSE;
    }
}

// this code runs over and over forever
void block_swap_block_loop(void) {
    if (o->oBlockSwapBlockAssignedSwitch != NULL) { // if we have a switch assigned (in other words, if o->oBlockSwapBlockAssignedSwitch  isn't NULL), do the following:

        if (o->oBlockSwapBlockColorRed) { // If our block is Red, make it follows it's assigned switch's Red color
            o->oBlockSwapBlockStateOn = o->oBlockSwapBlockAssignedSwitch->oBlockSwapSwitchStateOn;
        } else { // If our block is Blue, make it follows it's assigned switch's Blue color
            o->oBlockSwapBlockStateOn = !o->oBlockSwapBlockAssignedSwitch->oBlockSwapSwitchStateOn;
        }

        if (o->oBlockSwapBlockStateOn) { // If the block is ON, make it so Mario can stand on it !
            load_object_collision_model();
        }
        

    }
}