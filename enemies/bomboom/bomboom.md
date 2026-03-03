Hello ! My name's Lola, and here is one of the actors I made for everyone to use/inspect for free.
Below are instructions on how to set it up !

Issues or questions ? Reach out to me on discord ! @lolathesquishier
My Youtube where I post SM64 decomp tutorials : https://www.youtube.com/@lolathesquishy


Description of the actor: Bomboom is a tank that throws rolling bombs at Mario when he is close enough !
To be defeated, bomboom needs to be ground pounded ! The tank itself does not damage Mario, but the bombs does !
They explode after a few seconds or if Mario touches them
_________________________________________________________________________________________________________________________

Along with this instruction text file is a folder named 'files', you'll find subdirectories inside, paste the content of 'actors' in your
decomp folder's 'actors' folder, then paste the content of the 'behaviors' folder inside your decomp folder's 'src/game/behaviors' folder
then follow the next instructions !
_________________________________________________________________________________________________________________________

BLENDER:
When placing your object, model name should be 'MODEL_BOMBOOM' and behavior should be 'bhvBomboom' !
_________________________________________________________________________________________________________________________

in 'data/behavior_data.c' paste the following:
```
const BehaviorScript bhvBomboomBomb[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_INT(oFlags, OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 30, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    LOAD_ANIMATIONS(oAnimations, bomboom_bomb_anims),
    CALL_NATIVE(bomboom_bomb_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bomboom_bomb_loop),
    END_LOOP(),
};

const BehaviorScript bhvBomboom[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 60, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    LOAD_ANIMATIONS(oAnimations, bomboom_anims),
    LOAD_COLLISION_DATA(bomboom_collision),
    ANIMATE(0),
    CALL_NATIVE(bomboom_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bomboom_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};
```
_________________________________________________________________________________________________________________________

in 'include/behavior_data.h' paste the following:
```
extern const BehaviorScript bhvBomboomBomb[];
extern const BehaviorScript bhvBomboom[];
```
_________________________________________________________________________________________________________________________

in 'src/game/behavior_actions.h' paste the following:
```
Gfx *bomboom_bomb_color(s32 callContext, UNUSED struct GraphNode *node);
void bomboom_bomb_init(void);
void bomboom_bomb_loop(void);
void bomboom_init(void);
void bomboom_loop(void);
```
_________________________________________________________________________________________________________________________

in 'src/game/obj_behaviors_2.c' paste the following:
```
#include "behaviors/bomboom.inc.c"
```
_________________________________________________________________________________________________________________________

in 'include/object_fields.h' paste the following:
```
#define oBomboomBombTimer           OBJECT_FIELD_F32(0x1B)
#define oBomboomBombColorTimer      OBJECT_FIELD_F32(0x1C)
#define oBomboomBombCurrentColor    OBJECT_FIELD_S32(0x1D)
#define oBomboomBombTargetColor     OBJECT_FIELD_S32(0x1E)
#define oBomboomBombSpeed           OBJECT_FIELD_F32(0x1F)
#define oBomboomTimer               OBJECT_FIELD_F32(0x1B)
```
_________________________________________________________________________________________________________________________

in 'include/model_ids.h' paste the following:
```
#define MODEL_BOMBOOM_BOMB XXXaddAuniqueIDhereXXX
#define MODEL_BOMBOOM XXXaddAuniqueIDhereXXX
```
_________________________________________________________________________________________________________________________

in 'levels/scripts.c' paste the following in the object group you want it in:
```
LOAD_MODEL_FROM_GEO(MODEL_BOMBOOM_BOMB,      bomboom_bomb_geo),
LOAD_MODEL_FROM_GEO(MODEL_BOMBOOM,      bomboom_geo),
```
_________________________________________________________________________________________________________________________

in 'actors/YourGroup_geo.c' paste the following:
```
#include "bomboom_bomb/geo.inc.c"
#include "bomboom/geo.inc.c"
```

in 'actors/YourGroup.c' paste the following:
```
#include "bomboom_bomb/model.inc.c"
#include "bomboom_bomb/anims/data.inc.c"
#include "bomboom_bomb/anims/table.inc.c"
#include "bomboom/model.inc.c"
#include "bomboom/anims/data.inc.c"
#include "bomboom/anims/table.inc.c"
#include "bomboom/collision.inc.c"
```

in 'actors/YourGroup.h' paste the following:
```
#include "bomboom_bomb/geo_header.h"
#include "bomboom_bomb/anim_header.h"
#include "bomboom/geo_header.h"
#include "bomboom/anim_header.h"
#include "bomboom/collision_header.h"
```
_________________________________________________________________________________________________________________________
