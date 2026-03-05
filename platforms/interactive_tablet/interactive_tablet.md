Hello ! My name's Lola, and here is one of the actors I made for everyone to use/inspect for free.
Below are instructions on how to set it up !

Issues or questions ? Reach out to me on discord ! @lolathesquishier
My Youtube where I post SM64 decomp tutorials : https://www.youtube.com/@lolathesquishy


Description of the actor: In a set of Interactive Tablets, each tablet can be toggled ON or OFF by standing on it. if all the tablets are ON, they will change to a
third state that won't change further and the podium they are assigned to will spawn a star ! (See intructions below to set a star ID)
_________________________________________________________________________________________________________________________

Along with this instruction text file is a folder named 'files', you'll find subdirectories inside, paste the content of 'actors' in your
decomp folder's 'actors' folder, then paste the content of the 'behaviors' folder inside your decomp folder's 'src/game/behaviors' folder
then follow the next instructions !

IMPORTANT:
When placing any of those actors, the first 'Behavior Parameter' (for both the podium and the tablets) is what I call the 'ID' of the actor. Exemple : A star podium of ID 2 will ONLY spawn a star if all the tablets of ID 2 are toggled on !
The second parameter (only for the star podium) indicates the ID of the star (0 to 6).
Each tablet can only have 1 podium assigned to it but you can have multiple sets of tablets and podium at once in your world (exemple: 6 tile of ID 2 with
one podium of ID 2, and 4 tiles of ID 3 with a podium of ID 3).
_________________________________________________________________________________________________________________________

BLENDER:
When placing your object, model name should be 'MODEL_INTERACTIVE_TABLET' with a 'bhvInteractiveTablet' behavior for regular tiles !
When placing your object, model name should be 'MODEL_INTERACTIVE_TABLET_PODIUM' with a 'bhvInteractiveTabletPodium' behavior for where the star will spawn at !
_________________________________________________________________________________________________________________________

in 'data/behavior_data.c' paste the following:
```
const BehaviorScript bhvInteractiveTablet[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO),
    SET_FLOAT(oDrawingDistance, 10000),
    LOAD_COLLISION_DATA(interactive_tablet_collision),
    CALL_NATIVE(interactive_tablet_init),
    BEGIN_LOOP(),
        CALL_NATIVE(interactive_tablet_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};

const BehaviorScript bhvInteractiveTabletPodium[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oDrawingDistance, 10000),
    LOAD_COLLISION_DATA(interactive_tablet_podium_collision),
    CALL_NATIVE(interactive_tablet_podium_init),
    BEGIN_LOOP(),
        CALL_NATIVE(interactive_tablet_podium_loop),
        CALL_NATIVE(load_object_collision_model),
    END_LOOP(),
};
```
_________________________________________________________________________________________________________________________

in 'include/behavior_data.h' paste the following:
```
extern const BehaviorScript bhvInteractiveTablet[];
extern const BehaviorScript bhvInteractiveTabletPodium[];

```
_________________________________________________________________________________________________________________________

in 'src/game/behavior_actions.h' paste the following:
```
Gfx *interactive_tablet_state(s32 callContext, struct GraphNode *node);
void interactive_tablet_init(void);
void interactive_tablet_loop(void);
void interactive_tablet_podium_init(void);
void interactive_tablet_podium_loop(void);
```
_________________________________________________________________________________________________________________________

in 'src/game/obj_behaviors_2.c' paste the following:
```
#include "behaviors/interactive_tablet.inc.c"
```
_________________________________________________________________________________________________________________________

in 'include/object_fields.h' paste the following:
```
#define oInteractiveTabletState                  OBJECT_FIELD_S32(0x1B)
#define oInteractiveTabletIsPodium               OBJECT_FIELD_S32(0x1C)
#define oInteractiveTabletAssignedPodium         OBJECT_FIELD_OBJ(0x1D)
#define oInteractiveTabletAssignedTablet         OBJECT_FIELD_OBJ(0x1E)
#define oInteractiveTabletSetFinal               OBJECT_FIELD_S32(0x1F)
#define oInteractiveTabletPodiumSpawnStar        OBJECT_FIELD_S32(0x20)
#define oInteractiveTabletInteractTimer          OBJECT_FIELD_F32(0x21)
#define oInteractiveTabletCanInteract            OBJECT_FIELD_S32(0x22)
```
_________________________________________________________________________________________________________________________

in 'include/model_ids.h' paste the following:
```
#define MODEL_INTERACTIVE_TABLET            XXXaddAuniqueIDhereXXX
#define MODEL_INTERACTIVE_TABLET_PODIUM     XXXaddAuniqueIDhereXXX
```
_________________________________________________________________________________________________________________________

in 'levels/scripts.c' paste the following in the object group you want it in:
```
LOAD_MODEL_FROM_GEO(MODEL_INTERACTIVE_TABLET,      interactive_tablet_geo),
LOAD_MODEL_FROM_GEO(MODEL_INTERACTIVE_TABLET_PODIUM,      interactive_tablet_podium_geo),
```
_________________________________________________________________________________________________________________________

in 'actors/YourGroup_geo.c' paste the following:
```
#include "interactive_tablet/geo.inc.c"
#include "interactive_tablet_podium/geo.inc.c"
```

in 'actors/YourGroup.c' paste the following:
```
#include "interactive_tablet/model.inc.c"
#include "interactive_tablet/collision.inc.c"
#include "interactive_tablet_podium/collision.inc.c"
#include "interactive_tablet_podium/model.inc.c"
```

in 'actors/YourGroup.h' paste the following:
```
#include "interactive_tablet/geo_header.h"
#include "interactive_tablet/collision_header.h"
#include "interactive_tablet_podium/collision_header.h"
#include "interactive_tablet_podium/geo_header.h"
```
_________________________________________________________________________________________________________________________
