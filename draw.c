#include "cub3d.h"

t_state state;

void parser() {
	// state.map_height = 14;
	// state.map_width = 33;
	// state.map = malloc(state.map_height * sizeof(char *));
	// state.map[0] = "        1111111111111111111111111";
	// state.map[1] = "        1000000000110000000000001";
	// state.map[2] = "        1011000001110000000000001";
	// state.map[3] = "        1001000000000000000000001";
	// state.map[4] = "111111111011000001110000000000001";
	// state.map[5] = "100000000011000001110111111111111";
	// state.map[6] = "11110111111111011100000010001    ";
	// state.map[7] = "11110111111111011101010010001    ";
	// state.map[8] = "11000000110101011100000010001    ";
	// state.map[9] = "10000000000000001100000010001    ";
	// state.map[10] = "10000000000000001101010010001    ";
	// state.map[11] = "1100000111010101111101111000111  ";
	// state.map[12] = "11110111 1110101 101111010001    ";
	// state.map[13] = "11111111 1111111 111111111111    ";
	// state.px = 26;
	// state.py = 11;
	// state.sprite.sy = 1;
	// state.sprite.sx = 11;

	state.map_height = 8;
	state.map_width = 8;
	state.map = malloc(state.map_height * sizeof(char *));

	state.map[0] = "11111111";
	state.map[1] = "10100001";
	state.map[2] = "10100001";
	state.map[3] = "10100001";
	state.map[4] = "10000001";
	state.map[5] = "10000101";
	state.map[6] = "10000001";
	state.map[7] = "11111111";

	state.px = 6;
	state.py = 6;
	state.initial_orientation = north;

	state.north_texture.path = "./assets/0001.xpm";
	state.south_texture.path = "./assets/0001.xpm";
	state.west_texture.path = "./assets/0001.xpm";
	state.east_texture.path = "./assets/0001.xpm";

	state.c = COLOR(0x00, 0x66, 0xb2, 0xff);
	state.f = COLOR(0x00, 0xc0, 0xc0, 0xc0);

	state.sprite.path = "./assets/monster.xpm";
	state.sprite.sy = 2;
	state.sprite.sx = 3;
	state.sprite.__sz = 5;
}

void print_state() {
	printf("map_height: %d\n", state.map_height);
	printf("map_width: %d\n", state.map_width);
	printf("map: %p\n", state.map);
	printf("map: %d\n", state.initial_orientation);
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

void draw() {
	// parser();
	print_state();
	exit(1);

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

	init_window();
	read_img_from_xpm(state.north_texture.path, &state.north_texture.img_attr);
	read_img_from_xpm(state.south_texture.path, &state.south_texture.img_attr);
	read_img_from_xpm(state.west_texture.path, &state.west_texture.img_attr);
	read_img_from_xpm(state.east_texture.path, &state.east_texture.img_attr);
	read_img_from_xpm(state.sprite.path, &state.sprite.img_attr);

	render(&state);
	mlx_loop(state.__mlx);
}
