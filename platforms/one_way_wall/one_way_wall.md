Hello ! My name's Lola, and here is one of the actors I made for everyone to use/inspect for free.
Below are instructions on how to set it up !

Issues or questions ? Reach out to me on discord ! @lolathesquishier
My Youtube where I post SM64 decomp tutorials : https://www.youtube.com/@lolathesquishy


Description of the actor: One Way Walls are walls that lets you go through them, but....... Only from one direction !

_________________________________________________________________________________________________________________________

Along with this instruction text file is a folder named 'files', you'll find a subdirectory inside, paste the content of 'actors' in your
decomp folder's 'actors' folder then follow the next instructions !
_________________________________________________________________________________________________________________________

BLENDER:
When placing your object, model ID should be 'MODEL_ONE_WAY_WALL' with a 'bhvOneWayWall' behavior !
_________________________________________________________________________________________________________________________

in 'data/behavior_data.c' paste the following:
```
const BehaviorScript bhvOneWayWall[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(one_way_wall_collision),
    SET_FLOAT(oDrawingDistance, 5000),
    LOAD_ANIMATIONS(oAnimations, one_way_wall_anims),
    ANIMATE(0),
    BEGIN_LOOP(),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};
```
_________________________________________________________________________________________________________________________

in 'include/behavior_data.h' paste the following:
```
extern const BehaviorScript bhvOneWayWall[];
```
_________________________________________________________________________________________________________________________

in 'include/model_ids.h' paste the following:
```
#define MODEL_ONE_WAY_WALL                          XXXaddAuniqueIDhereXXX
```
_________________________________________________________________________________________________________________________

in 'levels/scripts.c' paste the following in the object group you want it in:
```
LOAD_MODEL_FROM_GEO(MODEL_ONE_WAY_WALL,      one_way_wall_geo),
```
_________________________________________________________________________________________________________________________

in 'actors/YourGroup_geo.c' paste the following:
```
#include "one_way_wall/geo.inc.c"

```

in 'actors/YourGroup.c' paste the following:
```
#include "one_way_wall/model.inc.c"
#include "one_way_wall/anims/data.inc.c"
#include "one_way_wall/anims/table.inc.c"
#include "one_way_wall/collision.inc.c"

```

in 'actors/YourGroup.h' paste the following:
```
#include "one_way_wall/geo_header.h"
#include "one_way_wall/anim_header.h"
#include "one_way_wall/collision_header.h"
```
_________________________________________________________________________________________________________________________
