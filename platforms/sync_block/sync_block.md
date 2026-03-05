Hello ! My name's Lola, and here is one of the actors I made for everyone to use/inspect for free.
Below are instructions on how to set it up !

Issues or questions ? Reach out to me on discord ! @lolathesquishier
My Youtube where I post SM64 decomp tutorials : https://www.youtube.com/@lolathesquishy


Description of the actor: Sync Blocks are Pinks and Cyan blocks that rhythmically change state from being On or Off after a few seconds
_________________________________________________________________________________________________________________________

Along with this instruction text file is a folder named 'files', you'll find subdirectories inside, paste the content of 'actors' in your
decomp folder's 'actors' folder, then paste the content of the 'behaviors' folder inside your decomp folder's 'src/game/behaviors' folder
then follow the next instructions !

IMPORTANT:
When placing this actors, the first 'Behavior Parameter' is the color of the actor. Exemple : less or equal to 1 means it'll be Pink, more than this will make it Blue !
_________________________________________________________________________________________________________________________

BLENDER:
When placing your object, model ID should be 'MODEL_SYNC_BLOCK' with a 'bhvSyncBlock' behavior !
_________________________________________________________________________________________________________________________

in 'data/behavior_data.c' paste the following:
```
const BehaviorScript bhvSyncBlock[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO),
    SET_FLOAT(oDrawingDistance, 10000),
    LOAD_COLLISION_DATA(sync_block_collision),
    CALL_NATIVE(sync_block_color_init),
    BEGIN_LOOP(),
        CALL_NATIVE(sync_block_color_loop),
    END_LOOP(),
};
```
_________________________________________________________________________________________________________________________

in 'include/behavior_data.h' paste the following:
```
extern const BehaviorScript bhvSyncBlock[];

```
_________________________________________________________________________________________________________________________

in 'src/game/behavior_actions.h' paste the following:
```
Gfx *sync_block_color(s32 callContext, struct GraphNode *node);
void sync_block_color_init(void);
void sync_block_color_loop(void);
```
_________________________________________________________________________________________________________________________

in 'src/game/obj_behaviors_2.c' paste the following:
```
#include "behaviors/sync_block.inc.c"
```
_________________________________________________________________________________________________________________________

in 'include/object_fields.h' paste the following:
```
#define oSyncBlockState                          OBJECT_FIELD_S32(0x1B)
#define oSyncBlockColor                          OBJECT_FIELD_S32(0x1C)
#define oSyncBlockTimer                          OBJECT_FIELD_F32(0x1D)
#define oSyncBlockCycle                          OBJECT_FIELD_F32(0x1E)
#define oSyncBlockTargetBlinkColor               OBJECT_FIELD_S32(0x1F)
#define oSyncBlockCurrentBlinkColor              OBJECT_FIELD_S32(0x20)
```
_________________________________________________________________________________________________________________________

in 'include/model_ids.h' paste the following:
```
#define MODEL_SYNC_BLOCK                    XXXaddAuniqueIDhereXXX
```
_________________________________________________________________________________________________________________________

in 'levels/scripts.c' paste the following in the object group you want it in:
```
LOAD_MODEL_FROM_GEO(MODEL_SYNC_BLOCK,      sync_block_geo),
```
_________________________________________________________________________________________________________________________

in 'actors/YourGroup_geo.c' paste the following:
```
#include "sync_block/geo.inc.c"
```

in 'actors/YourGroup.c' paste the following:
```
#include "sync_block/model.inc.c"
#include "sync_block/collision.inc.c"
```

in 'actors/YourGroup.h' paste the following:
```
#include "sync_block/geo_header.h"
#include "sync_block/collision_header.h"
```
_________________________________________________________________________________________________________________________
