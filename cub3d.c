#include "cub3d.h"

void die(char *msg) {
	perror(msg);
	exit(1);
}

void draw_frame() {
	raycasting();
	draw_sprite();
	draw_map();
}
