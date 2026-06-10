#include "table_enum.h"
const struct Animation *const skewer_anims[] = {
	[SKEWER_ANIM_SKEWER_ANIM_RETRACT] = &skewer_anim_skewer_anim_retract,
	[SKEWER_ANIM_SKEWER_ANIM_IDLE] = &skewer_anim_skewer_anim_idle,
	[SKEWER_ANIM_SKEWER_ANIM_PRE_LAUNCH] = &skewer_anim_skewer_anim_pre_launch,
	[SKEWER_ANIM_SKEWER_ANIM_EXTEND] = &skewer_anim_skewer_anim_extend,
};
