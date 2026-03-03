Hello ! My name's Lola, and here is one of the actors I made for everyone to use/inspect for free.
Below are instructions on how to set it up !

Issues or questions ? Reach out to me on discord ! @lolathesquishier
My Youtube where I post SM64 decomp tutorials : https://www.youtube.com/@lolathesquishy


Description of the actor: Croak is a frog that randomly roams around, it doesn't attack the player but it will damage
mario if he comes too close ! It also jumps at the same time as Mario if he jumps near it !
_________________________________________________________________________________________________________________________

Along with this instruction text file is a folder named 'files', you'll find subdirectories inside, paste the content of 'actors' in your
decomp folder's 'actors' folder, then paste the content of the 'behaviors' folder inside your decomp folder's 'src/game/behaviors' folder
then follow the next instructions !
_________________________________________________________________________________________________________________________

BLENDER:
When placing your object, model name should be 'MODEL_CROAK' and behavior should be 'bhvCroak' !
_________________________________________________________________________________________________________________________

in 'data/behavior_data.c' paste the following:
```
const BehaviorScript bhvCroak[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_INT(oFlags, OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 40, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    LOAD_ANIMATIONS(oAnimations, croak_anims),
    CALL_NATIVE(croak_init),
    BEGIN_LOOP(),
        CALL_NATIVE(croak_loop),
    END_LOOP(),
};
```
_________________________________________________________________________________________________________________________

in 'include/behavior_data.h' paste the following:
```
extern const BehaviorScript bhvCroak[];
```
_________________________________________________________________________________________________________________________

in 'src/game/behavior_actions.h' paste the following:
```
Gfx *croak_bubble(s32 callContext, struct GraphNode *node);
void croak_init(void);
void croak_loop(void);
```
_________________________________________________________________________________________________________________________

in 'src/game/obj_behaviors_2.c' paste the following:
```
#include "behaviors/croak.inc.c"
```
_________________________________________________________________________________________________________________________

in 'include/object_fields.h' paste the following:
```
#define oCroakBubbleTimer       OBJECT_FIELD_F32(0x1B)
#define oCroakActionTimer       OBJECT_FIELD_F32(0x1C)
#define oCroakJumpTimer         OBJECT_FIELD_F32(0x1D)
#define oCroakDirectionTarget   OBJECT_FIELD_F32(0x1E)
#define oCroakCanJump           OBJECT_FIELD_U32(0x1F)
#define oCroakSoundTimer        OBJECT_FIELD_F32(0x20)
```
_________________________________________________________________________________________________________________________

in 'include/model_ids.h' paste the following:
```
#define MODEL_CROAK XXXaddAuniqueIDhereXXX
```
_________________________________________________________________________________________________________________________

in 'levels/scripts.c' paste the following in the object group you want it in:
```
LOAD_MODEL_FROM_GEO(MODEL_CROAK,      croak_geo),
```
_________________________________________________________________________________________________________________________

in 'actors/YourGroup_geo.c' paste the following:
```
#include "croak/geo.inc.c"
```

in 'actors/YourGroup.c' paste the following:
```
#include "croak/model.inc.c"
#include "croak/anims/data.inc.c"
#include "croak/anims/table.inc.c"
```

in 'actors/YourGroup.h' paste the following:
```
#include "croak/geo_header.h"
#include "croak/anim_header.h"
```
_________________________________________________________________________________________________________________________
