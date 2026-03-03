Hello ! My name's Lola, and here is one of the actors I made for everyone to use/inspect for free.
Below are instructions on how to set it up !

Issues or questions ? Reach out to me on discord ! @lolathesquishier
My Youtube where I post SM64 decomp tutorials : https://www.youtube.com/@lolathesquishy


Description of the actor: Deceit is a chest mimic that patiently waits for Mario to come close.
It will lunge at Mario if he comes too close ! Mario cannot damage the deceit.
_________________________________________________________________________________________________________________________

Along with this instruction text file is a folder named 'files', you'll find subdirectories inside, paste the content of 'actors' in your
decomp folder's 'actors' folder, then paste the content of the 'behaviors' folder inside your decomp folder's 'src/game/behaviors' folder
then follow the next instructions !
_________________________________________________________________________________________________________________________

BLENDER:
When placing your object, model name should be 'MODEL_DECEIT' and behavior should be 'bhvDeceit' !
_________________________________________________________________________________________________________________________

in 'data/behavior_data.c' paste the following:
```
const BehaviorScript bhvDeceit[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 60, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    LOAD_ANIMATIONS(oAnimations, deceit_anims),
    SET_FLOAT(oDrawingDistance, 10000),
    CALL_NATIVE(deceit_init),
    BEGIN_LOOP(),
        CALL_NATIVE(deceit_loop),
    END_LOOP(),
};
```
_________________________________________________________________________________________________________________________

in 'include/behavior_data.h' paste the following:
```
extern const BehaviorScript bhvDeceit[];
```
_________________________________________________________________________________________________________________________

in 'src/game/behavior_actions.h' paste the following:
```
Gfx *deceit_light_proximity(s32 callContext, UNUSED struct GraphNode *node);
void deceit_init(void);
void deceit_loop(void);
```
_________________________________________________________________________________________________________________________

in 'src/game/obj_behaviors_2.c' paste the following:
```
#include "behaviors/deceit.inc.c"
```
_________________________________________________________________________________________________________________________

in 'include/object_fields.h' paste the following:
```
#define oDeceitTargetDirection      OBJECT_FIELD_S32(0x1B)
```
_________________________________________________________________________________________________________________________

in 'include/model_ids.h' paste the following:
```
#define MODEL_DECEIT XXXaddAuniqueIDhereXXX
```
_________________________________________________________________________________________________________________________

in 'levels/scripts.c' paste the following in the object group you want it in:
```
LOAD_MODEL_FROM_GEO(MODEL_DECEIT,      deceit_geo),
```
_________________________________________________________________________________________________________________________

in 'actors/YourGroup_geo.c' paste the following:
```
#include "deceit/geo.inc.c"
```

in 'actors/YourGroup.c' paste the following:
```
#include "deceit/model.inc.c"
#include "deceit/anims/data.inc.c"
#include "deceit/anims/table.inc.c"
```

in 'actors/YourGroup.h' paste the following:
```
#include "deceit/geo_header.h"
#include "deceit/anim_header.h"
```
_________________________________________________________________________________________________________________________

