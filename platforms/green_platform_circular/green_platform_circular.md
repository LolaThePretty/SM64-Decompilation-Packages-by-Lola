Hello ! My name's Lola, and here is one of the actors I made for everyone to use/inspect for free.
Below are instructions on how to set it up !

Issues or questions ? Reach out to me on discord ! @lolathesquishier
My Youtube where I post SM64 decomp tutorials : https://www.youtube.com/@lolathesquishy


Description of the actor: Green Platforms are platforms that move in a circle around the blender object's center !
You can edit all 4 parameters of the object to change it's properties ! (VALUES MUST ME BETWEEN 0x0 AND 0xFE ! NOT MORE THAN 0xFE !)

_________________________________________________________________________________________________________________________

Along with this instruction text file is a folder named 'files', you'll find subdirectories inside, paste the content of 'actors' in your
decomp folder's 'actors' folder, then paste the content of the 'behaviors' folder inside your decomp folder's 'src/game/behaviors' folder
then follow the next instructions !

IMPORTANT:
You can edit the following paremeters to change their properties :
1st param: 0x0/0x1 for 0x0 = horizontal circular path, 0x1 = vertical circular path
2nd param: 0xNUM where NUM is how many platform you want in the circle !
3rd param: 0xRADIUS where RADIUS is the radius of the circle path !
4th param: 0xSPEED where SPEED is the speed of the platforms !
_________________________________________________________________________________________________________________________

BLENDER:
When placing your object, model ID should be 'MODEL_NONE' with a 'bhvGreenPlatformCircularManager' behavior !
_________________________________________________________________________________________________________________________

in 'data/behavior_data.c' paste the following:
```
const BehaviorScript bhvGreenPlatformCircularManager[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    SET_FLOAT(oDrawingDistance, 10000),
    CALL_NATIVE(green_platform_manager_init),
    BREAK(),
};

const BehaviorScript bhvGreenPlatformCircular[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(green_platform_collision),
    SET_FLOAT(oDrawingDistance, 10000),
    SET_HOME(),
    CALL_NATIVE(green_platform_init),
    BEGIN_LOOP(),
        CALL_NATIVE(green_platform_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};
```
_________________________________________________________________________________________________________________________

in 'include/behavior_data.h' paste the following:
```
extern const BehaviorScript bhvGreenPlatformCircularManager[];
extern const BehaviorScript bhvGreenPlatformCircular[];
```
_________________________________________________________________________________________________________________________

in 'src/game/behavior_actions.h' paste the following:
```
void green_platform_manager_init(void);
void bhv_green_platform_manager_loop(void);
void green_platform_init(void);
void green_platform_loop(void);
```
_________________________________________________________________________________________________________________________

in 'src/game/obj_behaviors_2.c' paste the following:
```
#include "behaviors/green_platform.inc.c"
```
_________________________________________________________________________________________________________________________

in 'include/object_fields.h' paste the following:
```
#define oGreenPlatformRadius         OBJECT_FIELD_S32(0x1B)
#define oGreenPlatformSpeed          OBJECT_FIELD_S32(0x1C)
#define oGreenPlatformAmount         OBJECT_FIELD_S32(0x1D)
#define oGreenPlatformID             OBJECT_FIELD_S32(0x1E)
```
_________________________________________________________________________________________________________________________

in 'include/object_constants.h' paste the following:
```
#define GREEN_PLATFORM_CIRCULAR_HORIZONTAL               0x0
#define GREEN_PLATFORM_CIRCULAR_VERTICAL                 0x1
```
_________________________________________________________________________________________________________________________

in 'include/model_ids.h' paste the following:
```
#define MODEL_GREEN_PLATFORM                          XXXaddAuniqueIDhereXXX
#define MODEL_GREEN_PLATFORM_TRACK                    XXXaddAuniqueIDhereXXX
```
_________________________________________________________________________________________________________________________

in 'levels/scripts.c' paste the following in the object group you want it in:
```
LOAD_MODEL_FROM_GEO(MODEL_GREEN_PLATFORM,      green_platform_geo),
LOAD_MODEL_FROM_GEO(MODEL_GREEN_PLATFORM_TRACK,      green_platform_track_geo),
```
_________________________________________________________________________________________________________________________

in 'actors/YourGroup_geo.c' paste the following:
```
#include "green_platform/geo.inc.c"
#include "green_platform_track/geo.inc.c"

```

in 'actors/YourGroup.c' paste the following:
```
#include "green_platform/model.inc.c"
#include "green_platform/collision.inc.c"
#include "green_platform_track/model.inc.c"

```

in 'actors/YourGroup.h' paste the following:
```
#include "green_platform/geo_header.h"
#include "green_platform/collision_header.h"
#include "green_platform_track/geo_header.h"
```
_________________________________________________________________________________________________________________________
