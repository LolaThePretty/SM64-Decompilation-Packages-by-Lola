#include "src/game/envfx_snow.h"

const GeoLayout deceit_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, deceit_body_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_ASM(0, deceit_light_proximity),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 95, -75, -5, 0, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, deceit_000_lid_mesh_layer_1_with_revert),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_ALPHA, deceit_000_lid_mesh_layer_4_with_revert),
						GEO_DISPLAY_LIST(LAYER_TRANSPARENT, deceit_000_lid_mesh_layer_5_with_revert),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
