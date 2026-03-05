Hello ! My name's Lola, and here is one of the actors I made for everyone to use/inspect for free.
Below are instructions on how to set it up !

Issues or questions ? Reach out to me on discord ! @lolathesquishier
My Youtube where I post SM64 decomp tutorials : https://www.youtube.com/@lolathesquishy


Description of the actor: Silver stars are collectible little stars ! If all the silver star are collected, the podium they are assigned to will spawn a yellow star ! (See intructions below to set a star ID)
_________________________________________________________________________________________________________________________

Along with this instruction text file is a folder named 'files', you'll find subdirectories inside, paste the content of 'actors' in your
decomp folder's 'actors' folder, then paste the content of the 'behaviors' folder inside your decomp folder's 'src/game/behaviors' folder
then follow the next instructions !

IMPORTANT:
When placing any of those actors, the first 'Behavior Parameter' (for both the podium and the silver stars) is what I call the 'ID' of the actor. Exemple : A star podium of ID 2 will ONLY spawn a star if all the silver stars of ID 2 are collected !
The second parameter (only for the podium) indicates the ID of the yellow star (0 to 6).
Each silver star can only have 1 podium assigned to it but you can have multiple sets of silver stars and podium at once in your world (exemple: 6 silver stars of ID 2 with
one podium of ID 2, and 4 silver stars of ID 3 with a podium of ID 3).
_________________________________________________________________________________________________________________________

BLENDER:
When placing your object, model ID should be 'MODEL_SILVER_STAR' with a 'bhvSilverStar' behavior for silver stars !
When placing your object, model ID should be 'MODEL_SILVER_STAR_PODIUM' with a 'bhvSilverStarPodium' behavior for where the yellow star will spawn at !
_________________________________________________________________________________________________________________________

in 'data/behavior_data.c' paste the following:
```
const BehaviorScript bhvSilverStar[] = {
    BEGIN(OBJ_LIST_LEVEL),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO),
    SET_FLOAT(oDrawingDistance, 10000),
    LOAD_ANIMATIONS(oAnimations, silver_star_anims),
    ANIMATE(0),
    CALL_NATIVE(silver_star_init),
    BEGIN_LOOP(),
        CALL_NATIVE(silver_star_loop),
    END_LOOP(),
};

const BehaviorScript bhvSilverStarPodium[] = {
    BEGIN(OBJ_LIST_DEFAULT),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    SET_FLOAT(oDrawingDistance, 10000),
    CALL_NATIVE(silver_star_podium_init),
    BEGIN_LOOP(),
        CALL_NATIVE(silver_star_podium_loop),
    END_LOOP(),
};
```
_________________________________________________________________________________________________________________________

in 'include/behavior_data.h' paste the following:
```
extern const BehaviorScript bhvSilverStar[];
extern const BehaviorScript bhvSilverStarPodium[];

```
_________________________________________________________________________________________________________________________

in 'src/game/behavior_actions.h' paste the following:
```
Gfx *silver_star_size_func(s32 callContext, struct GraphNode *node);
void silver_star_init(void);
void silver_star_loop(void);
void silver_star_podium_init(void);
void silver_star_podium_loop(void);
```
_________________________________________________________________________________________________________________________

in 'src/game/obj_behaviors_2.c' paste the following:
```
#include "behaviors/silver_star.inc.c"
```
_________________________________________________________________________________________________________________________

in 'include/object_fields.h' paste the following:
```
#define oSilverStarScale                         OBJECT_FIELD_F32(0x1B)
#define oSilverStarTargetScale                   OBJECT_FIELD_F32(0x1C)
#define oSilverStarAssignedPodium                OBJECT_FIELD_OBJ(0x1D)
#define oSilverStarPodiumAssignedSilverStar      OBJECT_FIELD_OBJ(0x1E)
#define oSilverStarNum                           OBJECT_FIELD_S32(0x1F)
#define oSilverStarAccel                         OBJECT_FIELD_F32(0x20)
#define oSilverStarCollected                     OBJECT_FIELD_S32(0x21)
#define oSilverStarSpawnStar                     OBJECT_FIELD_S32(0x22)
```
_________________________________________________________________________________________________________________________

in 'include/model_ids.h' paste the following:
```
#define MODEL_SILVER_STAR                   XXXaddAuniqueIDhereXXX
#define MODEL_SILVER_STAR_PODIUM            XXXaddAuniqueIDhereXXX
```
_________________________________________________________________________________________________________________________

in 'levels/scripts.c' paste the following in the object group you want it in:
```
LOAD_MODEL_FROM_GEO(MODEL_SILVER_STAR,      silver_star_geo),
LOAD_MODEL_FROM_GEO(MODEL_SILVER_STAR_PODIUM,      silver_star_podium_geo),
```
_________________________________________________________________________________________________________________________

in 'actors/YourGroup_geo.c' paste the following:
```
#include "silver_star_podium/geo.inc.c"
#include "silver_star/geo.inc.c"
```

in 'actors/YourGroup.c' paste the following:
```
#include "silver_star_podium/model.inc.c"
#include "silver_star/model.inc.c"
#include "silver_star/anims/data.inc.c"
#include "silver_star/anims/table.inc.c"
```

in 'actors/YourGroup.h' paste the following:
```
#include "silver_star_podium/geo_header.h"
#include "silver_star/geo_header.h"
#include "silver_star/anim_header.h"
```
_________________________________________________________________________________________________________________________
