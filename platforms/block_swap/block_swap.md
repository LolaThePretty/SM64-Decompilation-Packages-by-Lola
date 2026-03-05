Hello ! My name's Lola, and here is one of the actors I made for everyone to use/inspect for free.
Below are instructions on how to set it up !

Issues or questions ? Reach out to me on discord ! @lolathesquishier
My Youtube where I post SM64 decomp tutorials : https://www.youtube.com/@lolathesquishy


Description of the actor: A Block Swap switch allows Mario to toggle on and off every Block Swap Blocks assigned to the switch.
Making them collidable/Go-Through. Each state has a different shape and look to differentiate them. Mario has to jump and hit the block from below, or he can also
ground pound on a switch to activate it ! Blocks even have proper shadows that gets enabled/disabled based on their state !
_________________________________________________________________________________________________________________________

Along with this instruction text file is a folder named 'files', you'll find subdirectories inside, paste the content of 'actors' in your
decomp folder's 'actors' folder, then paste the content of the 'behaviors' folder inside your decomp folder's 'src/game/behaviors' folder
then follow the next instructions !
_________________________________________________________________________________________________________________________

BLENDER:
When placing your object, model name should be 'MODEL_BLOCK_SWAP_SWITCH' with a 'bhvBlockSwapSwitch' behavior for the switch !
When placing your object, model name should be 'MODEL_BLOCK_SWAP_BLOCK' with a 'bhvBlockSwapBlock' behavior for every block !

IMPORTANT:
When placing any of those actors, the first 'Behavior Parameter' is what I call the 'ID' of the actor. Exemple : A block of ID 2 will ONLY be toggled if a switch of ID 2 is hit !
The second parameter is the starting state of the block/switch (Red(On), or Blue(Off)). Less or equal to 1 will make it Red, anything else will make it Blue !
Each block can only have 1 switch assigned to it but you can have multiple sets of blocks and switches at once in your world (exemple: 6 red/blue blocks of ID 2 with
one switch of ID 2, and 4 red/blue blocks of ID 3 with a switch of ID 3).
_________________________________________________________________________________________________________________________

in 'data/behavior_data.c' paste the following:
```
const BehaviorScript bhvBlockSwapSwitch[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO),
    SET_FLOAT(oDrawingDistance, 10000),
    LOAD_COLLISION_DATA(block_swap_switch_collision),
    CALL_NATIVE(block_swap_switch_init),
    BEGIN_LOOP(),
        CALL_NATIVE(block_swap_switch_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvBlockSwapBlock[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oDrawingDistance, 10000),
    LOAD_COLLISION_DATA(block_swap_block_collision),
    CALL_NATIVE(block_swap_block_init),
    BEGIN_LOOP(),
        CALL_NATIVE(block_swap_block_loop),
    END_LOOP(),
};
```
_________________________________________________________________________________________________________________________

in 'include/behavior_data.h' paste the following:
```
extern const BehaviorScript bhvBlockSwapSwitch[];
extern const BehaviorScript bhvBlockSwapBlock[];

```
_________________________________________________________________________________________________________________________

in 'src/game/behavior_actions.h' paste the following:
```
Gfx *block_swap_switch_func(s32 callContext, struct GraphNode *node);
void block_swap_switch_init(void);
void block_swap_switch_loop(void);

Gfx *block_swap_block_color_func(s32 callContext, struct GraphNode *node);
Gfx *block_swap_block_state_func(s32 callContext, struct GraphNode *node);
void block_swap_block_init(void);
void block_swap_block_loop(void);
```
_________________________________________________________________________________________________________________________

in 'src/game/obj_behaviors_2.c' paste the following:
```
#include "behaviors/block_swap.inc.c"
```
_________________________________________________________________________________________________________________________

in 'include/object_fields.h' paste the following:
```
#define oBlockSwapSwitchStateOn                  OBJECT_FIELD_S32(0x1B)
#define oBlockSwapSwitchTimer                    OBJECT_FIELD_F32(0x1C)
#define oBlockSwapSwitchIncrementTimer           OBJECT_FIELD_S32(0x1D)
#define oBlockSwapBlockStateOn                   OBJECT_FIELD_S32(0x1B)
#define oBlockSwapBlockColorRed                  OBJECT_FIELD_S32(0x1C)
#define oBlockSwapBlockAssignedSwitch            OBJECT_FIELD_OBJ(0x1D)
```
_________________________________________________________________________________________________________________________

in 'include/model_ids.h' paste the following:
```
#define MODEL_BLOCK_SWAP_SWITCH XXXaddAuniqueIDhereXXX
#define MODEL_BLOCK_SWAP_BLOCK XXXaddAuniqueIDhereXXX
```
_________________________________________________________________________________________________________________________

in 'levels/scripts.c' paste the following in the object group you want it in:
```
LOAD_MODEL_FROM_GEO(MODEL_BLOCK_SWAP_SWITCH,      block_swap_switch_geo),
LOAD_MODEL_FROM_GEO(MODEL_BLOCK_SWAP_BLOCK,      block_swap_block_geo),
```
_________________________________________________________________________________________________________________________

in 'actors/YourGroup_geo.c' paste the following:
```
#include "block_swap_switch/geo.inc.c"
#include "block_swap_block/geo.inc.c"
```

in 'actors/YourGroup.c' paste the following:
```
#include "block_swap_switch/collision.inc.c"
#include "block_swap_switch/model.inc.c"
#include "block_swap_block/model.inc.c"
#include "block_swap_block/collision.inc.c"
```

in 'actors/YourGroup.h' paste the following:
```
#include "block_swap_switch/collision_header.h"
#include "block_swap_switch/geo_header.h"
#include "block_swap_block/geo_header.h"
#include "block_swap_block/collision_header.h"
```
_________________________________________________________________________________________________________________________
