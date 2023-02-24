#include "cub3d.h"

void draw_map_pixel(t_state *_state, int x, int y) {
	for (int j = mapY(y); j < mapY(y) + mapS; j++) {
		for (int i = mapX(x); i < mapX(x) + mapS; i++) {
			buffered_pixel_put(_state, i, j, MAP[y][x]);
		}
	}
}

void draw_map(t_state *state) {
	for (int j = 0; j < state->map_height; j++) {
		for (int i = 0; i < state->map_length; i++) {
			draw_map_pixel(state, i, j);
		}
	}
}

int is_wall(int x, int y) {
	x /= mapS;
	y /= mapS;

	if (x >= 0 && x < state.map_length
		&& y >= 0 && y < state.map_height
	)
		return IS_WALL(MAP[y][x]);
	return 0;
}