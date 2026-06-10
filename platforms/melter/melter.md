Hello ! My name's Lola, and here is one of the actors I made for everyone to use/inspect for free.
Below are instructions on how to set it up !

Issues or questions ? Reach out to me on discord ! @lolathesquishier
My Youtube where I post SM64 decomp tutorials : https://www.youtube.com/@lolathesquishy


Description of the actor: Melters are flame throwers ! Place them in any direction you may want ! :D
They can start either on or off (exemple one will be active while the other rest, and vice versa !)
_________________________________________________________________________________________________________________________

Along with this instruction text file is a folder named 'files', you'll find subdirectories inside, paste the content of 'actors' in your
decomp folder's 'actors' folder, then paste the content of the 'behaviors' folder inside your decomp folder's 'src/game/behaviors' folder
then follow the next instructions !

IMPORTANT:
You can edit the following paremeters to change their properties :
1st param: 0x1 = Melter starts already on, 0xAnythingElse = Melter starts off !

_________________________________________________________________________________________________________________________

BLENDER:
When placing your object, model ID should be 'MODEL_MELTER' with a 'bhvMelter' behavior !
_________________________________________________________________________________________________________________________

in 'data/behavior_data.c' paste the following:
```
const BehaviorScript bhvMelter[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)),
    LOAD_COLLISION_DATA(melter_collision),
    SET_FLOAT(oDrawingDistance, 5000),
    CALL_NATIVE(melter_init),
    BEGIN_LOOP(),
        CALL_NATIVE(melter_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvMelterFlame[] = {
    BEGIN(OBJ_LIST_GENACTOR),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    CALL_NATIVE(melter_flame_init),
    BEGIN_LOOP(),
        CALL_NATIVE(melter_flame_loop),
    END_LOOP(),
};
```
_________________________________________________________________________________________________________________________

in 'include/behavior_data.h' paste the following:
```
extern const BehaviorScript bhvMelter[];
extern const BehaviorScript bhvMelterFlame[];
```
_________________________________________________________________________________________________________________________

in 'src/game/behavior_actions.h' paste the following:
```
Gfx *melter_flame_scale(s32 callContext, struct GraphNode *node);
void melter_init(void);
void melter_loop(void);
void melter_flame_init(void);
void melter_flame_loop(void);
```
_________________________________________________________________________________________________________________________

in 'src/game/obj_behaviors_2.c' paste the following:
```
#include "behaviors/melter.inc.c"
```
_________________________________________________________________________________________________________________________

in 'include/object_fields.h' paste the following:
```
#define oMelterFlameScale            OBJECT_FIELD_F32(0x1B)
#define oMelterState                 OBJECT_FIELD_S32(0x1C)
#define oMelterTimer                 OBJECT_FIELD_F32(0x1D)
#define oMelterDamageTimer           OBJECT_FIELD_F32(0x1E)
```
_________________________________________________________________________________________________________________________

in 'include/model_ids.h' paste the following:
```
#define MODEL_MELTER                          XXXaddAuniqueIDhereXXX
```
_________________________________________________________________________________________________________________________

in 'levels/scripts.c' paste the following in the object group you want it in:
```
LOAD_MODEL_FROM_GEO(MODEL_MELTER,      melter_geo),
```
_________________________________________________________________________________________________________________________

in 'actors/YourGroup_geo.c' paste the following:
```
#include "melter/geo.inc.c"

```

in 'actors/YourGroup.c' paste the following:
```
#include "melter/model.inc.c"
#include "melter/collision.inc.c"

```

in 'actors/YourGroup.h' paste the following:
```
#include "melter/geo_header.h"
#include "melter/collision_header.h"
```
_________________________________________________________________________________________________________________________
