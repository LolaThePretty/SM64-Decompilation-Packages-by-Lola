#include "src/game/envfx_snow.h"

const GeoLayout one_way_wall_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, one_way_wall_root_mesh_layer_5),
		GEO_OPEN_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 200, -225, 90, 0, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, one_way_wall_arrow_1_mesh_layer_5),
			GEO_CLOSE_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 200, -400, 90, 0, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, one_way_wall_arrow_2_mesh_layer_5_with_revert),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
