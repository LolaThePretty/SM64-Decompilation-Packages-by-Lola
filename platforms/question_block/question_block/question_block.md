Hello ! My name's Lola, and here is one of the actors I made for everyone to use/inspect for free.
Below are instructions on how to set it up !

Issues or questions ? Reach out to me on discord ! @lolathesquishier
My Youtube where I post SM64 decomp tutorials : https://www.youtube.com/@lolathesquishy


Description of the actor: Question Blocks contains goodies ! You can easily tell the game what object (or enemy hehe!) you want to spawn from em !
_________________________________________________________________________________________________________________________

Along with this instruction text file is a folder named 'files', you'll find subdirectories inside, paste the content of 'actors' in your
decomp folder's 'actors' folder, then paste the content of the 'behaviors' folder inside your decomp folder's 'src/game/behaviors' folder
then follow the next instructions !

IMPORTANT:
You can edit the following paremeters to change their properties :
1st param: 0x0 up to 0xFE ! Each item you add can be picked to spawn once the block is destroyed using this parameter !
_________________________________________________________________________________________________________________________

BLENDER:
When placing your object, model ID should be 'MODEL_QUESTION_BLOCK' with a 'bhvQuestionBlock' behavior !
_________________________________________________________________________________________________________________________

in 'data/behavior_data.c' paste the following:
```
const BehaviorScript bhvQuestionBlock[] = {
    BEGIN(OBJ_LIST_SURFACE),
    OR_INT(oFlags, OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE),
    LOAD_COLLISION_DATA(question_block_collision),
    CALL_NATIVE(question_block_init),
    BEGIN_LOOP(),
        CALL_NATIVE(question_block_loop),
    END_LOOP(),
};
```
_________________________________________________________________________________________________________________________

in 'include/behavior_data.h' paste the following:
```
extern const BehaviorScript bhvQuestionBlock[];
```
_________________________________________________________________________________________________________________________

in 'src/game/behavior_actions.h' paste the following:
```
void question_block_init(void);
void question_block_loop(void);
```
_________________________________________________________________________________________________________________________

in 'src/game/obj_behaviors_2.c' paste the following:
```
#include "behaviors/question_block.inc.c"
```
_________________________________________________________________________________________________________________________

in 'include/model_ids.h' paste the following:
```
#define MODEL_QUESTION_BLOCK                          XXXaddAuniqueIDhereXXX
```
_________________________________________________________________________________________________________________________

in 'levels/scripts.c' paste the following in the object group you want it in:
```
LOAD_MODEL_FROM_GEO(MODEL_QUESTION_BLOCK,      question_block_geo),
```
_________________________________________________________________________________________________________________________

in 'actors/YourGroup_geo.c' paste the following:
```
#include "question_block/geo.inc.c"

```

in 'actors/YourGroup.c' paste the following:
```
#include "question_block/model.inc.c"
#include "question_block/collision.inc.c"

```

in 'actors/YourGroup.h' paste the following:
```
#include "question_block/geo_header.h"
#include "question_block/collision_header.h"
```
_________________________________________________________________________________________________________________________
