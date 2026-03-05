Hello ! My name's Lola, and here is one of the actors I made for everyone to use/inspect for free.
Below are instructions on how to set it up !

Issues or questions ? Reach out to me on discord ! @lolathesquishier
My Youtube where I post SM64 decomp tutorials : https://www.youtube.com/@lolathesquishy


Description of the actor: A Fading Platform will slowly shrink in size until it's gone as soon as mario starts to stand on it !
They will come back after 10 seconds, becoming bigger quickly until they are back to their original size.
_________________________________________________________________________________________________________________________

Along with this instruction text file is a folder named 'files', you'll find subdirectories inside, paste the content of 'actors' in your
decomp folder's 'actors' folder, then paste the content of the 'behaviors' folder inside your decomp folder's 'src/game/behaviors' folder
then follow the next instructions !
_________________________________________________________________________________________________________________________

BLENDER:
When placing your object, model name should be 'MODEL_FADING_PLATFORM' with a 'bhvFadingPlatform' behavior !
_________________________________________________________________________________________________________________________

in 'data/behavior_data.c' paste the following:
```
const BehaviorScript bhvFadingPlatform[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oDrawingDistance, 10000),
    LOAD_COLLISION_DATA(fading_platform_collision),
    CALL_NATIVE(fading_platform_init),
    BEGIN_LOOP(),
        CALL_NATIVE(fading_platform_loop),
    END_LOOP(),
};
```
_________________________________________________________________________________________________________________________

in 'include/behavior_data.h' paste the following:
```
extern const BehaviorScript bhvFadingPlatform[];

```
_________________________________________________________________________________________________________________________

in 'src/game/behavior_actions.h' paste the following:
```
Gfx *fading_platform_scale(s32 callContext, struct GraphNode *node);
void fading_platform_init(void);
void fading_platform_loop(void);
```
_________________________________________________________________________________________________________________________

in 'src/game/obj_behaviors_2.c' paste the following:
```
#include "behaviors/fading_platform.inc.inc.c"
```
_________________________________________________________________________________________________________________________

in 'include/object_fields.h' paste the following:
```
#define oFadingPlatformScale                     OBJECT_FIELD_F32(0x1B)
#define oFadingPlatformVanishing                 OBJECT_FIELD_S32(0x1C)
#define oFadingPlatformTargetScale               OBJECT_FIELD_F32(0x1D)
#define oFadingPlatformTimerIdle                 OBJECT_FIELD_F32(0x1E)
```
_________________________________________________________________________________________________________________________

in 'include/model_ids.h' paste the following:
```
#define MODEL_FADING_PLATFORM XXXaddAuniqueIDhereXXX
```
_________________________________________________________________________________________________________________________

in 'levels/scripts.c' paste the following in the object group you want it in:
```
LOAD_MODEL_FROM_GEO(MODEL_FADING_PLATFORM,      fading_platform_geo),
```
_________________________________________________________________________________________________________________________

in 'actors/YourGroup_geo.c' paste the following:
```
#include "fading_platform/geo.inc.c"
```

in 'actors/YourGroup.c' paste the following:
```
#include "fading_platform/collision.inc.c"
#include "fading_platform/model.inc.c"
```

in 'actors/YourGroup.h' paste the following:
```
#include "fading_platform/collision_header.h"
#include "fading_platform/geo_header.h"
```
_________________________________________________________________________________________________________________________
