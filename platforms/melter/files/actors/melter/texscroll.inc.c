void scroll_melter_flame_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 297;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(melter_flame_mesh_layer_5_vtx_0);

	deltaX = (int)(-3.5 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_melter_flame_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 134;
	int width = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(melter_flame_mesh_layer_5_vtx_1);

	deltaX = (int)(2.5 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_actor_geo_melter() {
	scroll_melter_flame_mesh_layer_5_vtx_0();
	scroll_melter_flame_mesh_layer_5_vtx_1();
};
