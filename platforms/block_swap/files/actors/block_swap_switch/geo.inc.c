#include "src/game/envfx_snow.h"

const GeoLayout block_swap_switch_geo_opt_1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 100, 0, block_swap_switch_body_mesh_layer_1_opt_1_with_revert),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout block_swap_switch_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(11, 255, 400),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, -100, 0, NULL),
			GEO_OPEN_NODE(),
				GEO_SWITCH_CASE(0, block_swap_switch_func),
				GEO_OPEN_NODE(),
					GEO_NODE_START(),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 100, 0, block_swap_switch_body_mesh_layer_1_with_revert),
					GEO_CLOSE_NODE(),
					GEO_BRANCH(1, block_swap_switch_geo_opt_1),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
