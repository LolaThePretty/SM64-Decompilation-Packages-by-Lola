void scroll_bomboom_root_mesh_layer_1_vtx_1() {
	int i = 0;
	int count = 190;
	int height = 32 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bomboom_root_mesh_layer_1_vtx_1);

	deltaY = (int)(1.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_gfx_mat_bomboom_bomboom_main() {
	Gfx *mat = segmented_to_virtual(mat_bomboom_bomboom_main);

	shift_t(mat, 9, PACK_TILESIZE(0, 1));

};

void scroll_gfx_mat_bomboom_bomboom_tracks() {
	Gfx *mat = segmented_to_virtual(mat_bomboom_bomboom_tracks);

	shift_t(mat, 9, PACK_TILESIZE(0, 1));

};

void scroll_actor_geo_bomboom() {
	scroll_bomboom_root_mesh_layer_1_vtx_1();
	scroll_gfx_mat_bomboom_bomboom_main();
	scroll_gfx_mat_bomboom_bomboom_tracks();
};
