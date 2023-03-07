#include "cub3d.h"

t_state state;

// TODO: delete this
void print_state() {
	printf("map_height: %d\n", state.map_height);
	printf("map_width: %d\n", state.map_width);
	for (int i=0; i < state.map_height; i++) {
		printf("|%s|\n", state.map[i]);
	}
	printf("px: %d\n", state.px);
	printf("py: %d\n", state.py);
	printf("north_texture: %s\n", state.north_texture.path);
	printf("south_texture: %s\n", state.south_texture.path);
	printf("east_texture: %s\n", state.east_texture.path);
	printf("west_texture: %s\n", state.west_texture.path);
	printf("sprite: %s\n", state.sprite.path);
	printf("f: %d\n", state.f);
	printf("c: %d\n", state.c);
	printf("elem: %d\n", state.elem);
	printf("flag: %d\n", state.flag);
}

// TODO: delete this
void parser_stub() {
	print_state();
	state.map_width = 8;

	state.door_texture.path = "./assets/door2.xpm";
	state.sprite.path = "./assets/mushroom_cloud.xpm";
	state.sprite.sy = 2;
	state.sprite.sx = 3;
	state.sprite.__sz = 5;
	state.sprite.rows = 4;
	state.sprite.cols = 5;
}

void draw() {
	parser_stub();

	state.__fov = M_PI / 2;
	state.__ray_offset = 0.001;
	state.__pa = -(M_PI / 2) * state.initial_orientation;
	state.__line_count = state.__fov / state.__ray_offset;
	state.__line_thickness = WIDTH / state.__line_count;

	state.__zbuffer = malloc((state.__line_count + 1) * sizeof(*state.__zbuffer));

	state.__px = state.px * mapS + mapS/2;
	state.__py = state.py * mapS + mapS/2;
	state.sprite.__sx = state.sprite.sx * mapS + mapS/2;
	state.sprite.__sy = state.sprite.sy * mapS + mapS/2;
	state.sprite.__sz = 5;

	init_window();
	read_img_from_xpm(state.north_texture.path, &state.north_texture.img_attr);
	read_img_from_xpm(state.south_texture.path, &state.south_texture.img_attr);
	read_img_from_xpm(state.west_texture.path, &state.west_texture.img_attr);
	read_img_from_xpm(state.east_texture.path, &state.east_texture.img_attr);
	read_img_from_xpm(state.sprite.path, &state.sprite.img_attr);
	read_img_from_xpm(state.door_texture.path, &state.door_texture.img_attr);

	state.sprite.__x_off = 0;
	state.sprite.__y_off = 0;
	state.sprite.__unit_width = state.sprite.img_attr.width / state.sprite.cols;
	state.sprite.__unit_height = state.sprite.img_attr.height / state.sprite.rows;

	render(&state);
	mlx_loop(state.__mlx);
}
