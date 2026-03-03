Hello ! My name's Lola, and here is one of the actors I made for everyone to use/inspect for free.
Below are instructions on how to set it up !

Issues or questions ? Reach out to me on discord ! @lolathesquishier
My Youtube where I post SM64 decomp tutorials : https://www.youtube.com/@lolathesquishy


Description of the actor: Bugster is a tiny bug that randomly roams around unless Mario is nearby, in which case it will hunt him down !
It doesn't do damage but it does attack and bully Mario ! Each Bugster actor you place will summon a random small amount of minions that will
swarm with him ! They will all collectively attack Mario if he is too close !
_________________________________________________________________________________________________________________________

Along with this instruction text file is a folder named 'files', you'll find subdirectories inside, paste the content of 'actors' in your
decomp folder's 'actors' folder, then paste the content of the 'behaviors' folder inside your decomp folder's 'src/game/behaviors' folder
then follow the next instructions !
_________________________________________________________________________________________________________________________

BLENDER:
When placing your object, model name should be 'MODEL_BUGSTER' and behavior should be 'bhvBugsterLeader' !
_________________________________________________________________________________________________________________________

in 'data/behavior_data.c' paste the following:
```
const BehaviorScript bhvBugsterLeader[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_INT(oFlags, OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 40, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    LOAD_ANIMATIONS(oAnimations, bugster_anims),
    SET_HOME(),
    CALL_NATIVE(bugster_leader_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bugster_loop),
    END_LOOP(),
};

const BehaviorScript bhvBugsterMinion[] = {
    BEGIN(OBJ_LIST_PUSHABLE),
    OR_INT(oFlags, OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL | OBJ_FLAG_MOVE_XZ_USING_FVEL | OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_OBJ_PHYSICS(/*Wall hitbox radius*/ 40, /*Gravity*/ -400, /*Bounciness*/ 0, /*Drag strength*/ 1000, /*Friction*/ 1000, /*Buoyancy*/ 0, /*Unused*/ 0, 0),
    LOAD_ANIMATIONS(oAnimations, bugster_anims),
    SET_HOME(),
    CALL_NATIVE(bugster_minion_init),
    BEGIN_LOOP(),
        CALL_NATIVE(bugster_loop),
    END_LOOP(),
};
```
_________________________________________________________________________________________________________________________

in 'include/behavior_data.h' paste the following:
```
extern const BehaviorScript bhvBugsterLeader[];
extern const BehaviorScript bhvBugsterMinion[];
```
_________________________________________________________________________________________________________________________

in 'src/game/behavior_actions.h' paste the following:
```
void bugster_leader_init(void);
void bugster_minion_init(void);
void bugster_loop(void);
```
_________________________________________________________________________________________________________________________

in 'src/game/obj_behaviors_2.c' paste the following:
```
#include "behaviors/bugster.inc.c"
```
_________________________________________________________________________________________________________________________

in 'include/object_fields.h' paste the following:
```
#define oBugsterActionTimer         OBJECT_FIELD_F32(0x1B)
#define oBugsterDirectionTimer      OBJECT_FIELD_F32(0x1C)
#define oBugsterTargetDirection     OBJECT_FIELD_S32(0x1D)
#define oBugsterIsLeader            OBJECT_FIELD_U32(0x1E)
#define oBugsterLeaderActor         OBJECT_FIELD_OBJ(0x1F)
```
_________________________________________________________________________________________________________________________

in 'include/model_ids.h' paste the following:
```
#define MODEL_BUGSTER XXXaddAuniqueIDhereXXX
```
_________________________________________________________________________________________________________________________

in 'levels/scripts.c' paste the following in the object group you want it in:
```
LOAD_MODEL_FROM_GEO(MODEL_BUGSTER,      bugster_geo),
```
_________________________________________________________________________________________________________________________

in 'actors/YourGroup_geo.c' paste the following:
```
#include "bugster/geo.inc.c"
```

in 'actors/YourGroup.c' paste the following:
```
#include "bugster/model.inc.c"
#include "bugster/anims/data.inc.c"
#include "bugster/anims/table.inc.c"
```

in 'actors/YourGroup.h' paste the following:
```
#include "bugster/geo_header.h"
#include "bugster/anim_header.h"
```
_________________________________________________________________________________________________________________________
