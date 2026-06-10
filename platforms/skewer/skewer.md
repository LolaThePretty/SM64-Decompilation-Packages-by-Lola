Hello ! My name's Lola, and here is one of the actors I made for everyone to use/inspect for free.
Below are instructions on how to set it up !

Issues or questions ? Reach out to me on discord ! @lolathesquishier
My Youtube where I post SM64 decomp tutorials : https://www.youtube.com/@lolathesquishy


Description of the actor: Skewers are giant spiked collumns, they twist and extend to smash against floors, walls, (maybe even Mario !) and ceilings !
Then they retract and gets ready to repeat this behavior !
_________________________________________________________________________________________________________________________

Along with this instruction text file is a folder named 'files', you'll find subdirectories inside, paste the content of 'actors' in your
decomp folder's 'actors' folder, then paste the content of the 'behaviors' folder inside your decomp folder's 'src/game/behaviors' folder
then follow the next instructions !
_________________________________________________________________________________________________________________________

BLENDER:
When placing your object, model ID should be 'MODEL_SKEWER_BASE' with a 'bhvSkewerBase' behavior !
_________________________________________________________________________________________________________________________

in 'data/behavior_data.c' paste the following:
```
const BehaviorScript bhvSkewerBase[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(skewer_base_collision),
    SET_FLOAT(oDrawingDistance, 10000),
    SET_FLOAT(oCollisionDistance, 10000),
    CALL_NATIVE(skewer_base_init),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvSkewer[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_ANIMATIONS(oAnimations, skewer_anims),
    LOAD_COLLISION_DATA(skewer_collision),
    SET_FLOAT(oDrawingDistance, 10000),
    SET_FLOAT(oCollisionDistance, 10000),
    SET_HOME(),
    CALL_NATIVE(skewer_init),
    BEGIN_LOOP(),
        CALL_NATIVE(skewer_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvSkewerDamage[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    CALL_NATIVE(skewer_damage_init),
    BEGIN_LOOP(),
        CALL_NATIVE(skewer_damage_loop),
    END_LOOP(),
};
```
_________________________________________________________________________________________________________________________

in 'include/behavior_data.h' paste the following:
```
extern const BehaviorScript bhvSkewerBase[];
extern const BehaviorScript bhvSkewer[];
extern const BehaviorScript bhvSkewerDamage[];
```
_________________________________________________________________________________________________________________________

in 'src/game/behavior_actions.h' paste the following:
```
void skewer_base_init(void);
void skewer_init(void);
void skewer_loop(void);
void skewer_damage_init(void);
void skewer_damage_loop(void);
```
_________________________________________________________________________________________________________________________

in 'src/game/obj_behaviors_2.c' paste the following:
```
#include "behaviors/skewer.inc.c"
```
_________________________________________________________________________________________________________________________

in 'include/object_fields.h' paste the following:
```
#define oSkewerDamageTimer           OBJECT_FIELD_F32(0x1B)
#define oSkewerIdleTimer             OBJECT_FIELD_F32(0x1C)
#define oSkewerTopPosX               OBJECT_FIELD_F32(0x1D)
#define oSkewerTopPosY               OBJECT_FIELD_F32(0x1E)
#define oSkewerTopPosZ               OBJECT_FIELD_F32(0x1F)
#define oSkewerRetractPosX           OBJECT_FIELD_F32(0x20)
#define oSkewerRetractPosY           OBJECT_FIELD_F32(0x21)
#define oSkewerRetractPosZ           OBJECT_FIELD_F32(0x22)
#define oSkewerPreLaunchPosX         OBJECT_FIELD_F32(0x23)
#define oSkewerPreLaunchPosY         OBJECT_FIELD_F32(0x24)
#define oSkewerPreLaunchPosZ         OBJECT_FIELD_F32(0x25)
```
_________________________________________________________________________________________________________________________

in 'include/object_constants.h' paste the following:
```
#define SKEWER_RETRACT                  0x0
#define SKEWER_IDLE                     0x1
#define SKEWER_PRE_LAUNCH               0x2
#define SKEWER_EXTEND                   0x3
#define SKEWER_IDLE_EXTENDED            0x4
```
_________________________________________________________________________________________________________________________

in 'include/model_ids.h' paste the following:
```
#define MODEL_SKEWER_BASE                          XXXaddAuniqueIDhereXXX
#define MODEL_SKEWER                               XXXaddAuniqueIDhereXXX
```
_________________________________________________________________________________________________________________________

in 'levels/scripts.c' paste the following in the object group you want it in:
```
LOAD_MODEL_FROM_GEO(MODEL_SKEWER_BASE,      skewer_base_geo),
LOAD_MODEL_FROM_GEO(MODEL_SKEWER,      skewer_geo),
```
_________________________________________________________________________________________________________________________

in 'actors/YourGroup_geo.c' paste the following:
```
#include "skewer_base/geo.inc.c"
#include "skewer/geo.inc.c"

```

in 'actors/YourGroup.c' paste the following:
```
#include "skewer_base/collision.inc.c"
#include "skewer_base/model.inc.c"
#include "skewer/collision.inc.c"
#include "skewer/model.inc.c"
#include "skewer/anims/data.inc.c"
#include "skewer/anims/table.inc.c"

```

in 'actors/YourGroup.h' paste the following:
```
#include "skewer_base/collision_header.h"
#include "skewer_base/geo_header.h"
#include "skewer/collision_header.h"
#include "skewer/geo_header.h"
#include "skewer/anim_header.h"
```
_________________________________________________________________________________________________________________________
