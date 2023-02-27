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

	init_window();
	render(&state);
	mlx_loop(state.mlx);
}
