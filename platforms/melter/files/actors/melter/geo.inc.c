#include "src/game/envfx_snow.h"

const GeoLayout melter_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, melter_root_mesh_layer_1_with_revert),
		GEO_OPEN_NODE(),
			GEO_ASM(0, melter_flame_scale),
			GEO_SCALE(LAYER_OPAQUE, 65536),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 55, 0, melter_flame_mesh_layer_5_with_revert),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
