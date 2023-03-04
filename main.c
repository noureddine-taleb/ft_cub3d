#include "cub3d.h"

#define MAP_LENGTH 8
#define MAP_HEIGHT 8

int map[MAP_HEIGHT][MAP_LENGTH] = {
	{ WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE },
	{ WHITE, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK, WHITE },
	{ WHITE, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK, WHITE },
	{ WHITE, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK, WHITE },
	{ WHITE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, WHITE },
	{ WHITE, BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, WHITE },
	{ WHITE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, WHITE },
	{ WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE },
};

t_state state;

int main() {
	state.map = (int *)&map;
	state.map_height = MAP_HEIGHT;
	state.map_length = MAP_LENGTH;

	state.px = 200;
	state.py = 200;
	state.pa = -M_PI / 2;
	state.fov = M_PI / 2;
	state.ray_offset = 0.001;

	state.__line_count = state.fov / state.ray_offset;
	state.__line_thickness = WIDTH / state.__line_count;
	state.zbuffer = malloc((state.__line_count + 1) * sizeof(double));

	state.wall_texture.path = "./assets/0001.xpm";
	state.monster_sprite.path = "./assets/monster.xpm";
	state.monster_sprite.mx = 200;
	state.monster_sprite.my = 100;
	state.monster_sprite.dist = INFINITY;

	init_window();
	read_texture(&state.wall_texture);
	read_sprite(&state.monster_sprite);

	render(&state);
	mlx_loop(state.mlx);
}
