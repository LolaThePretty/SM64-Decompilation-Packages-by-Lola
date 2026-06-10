#include "src/game/envfx_snow.h"

const GeoLayout skewer_base_geo[] = {
	GEO_CULLING_RADIUS(5000),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, skewer_base_root_mesh_layer_1_with_revert),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
