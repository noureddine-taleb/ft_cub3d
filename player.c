#include "cub3d.h"

#define pS 8

void cast_ray(t_state *state, int x, int y, double angle, int color) {
	double dx = cos(angle);
	double dy = sin(angle);
	double x0 = x;
	double y0 = y;

	while (
		y0 >= 0 && y0 < state->map_height * mapS
		&& x0 >= 0 && x0 < state->map_length * mapS
	) {
		if (is_wall(x0, y0))
			return;
		buffered_pixel_put(state, x0, y0, color);
		x0 += dx;
		y0 += dy;
	}
}

void draw_player(t_state *state) {
	for (int j = state->py; j < state->py + pS; j++) {
		for (int i = state->px; i < state->px + pS; i++) {
			buffered_pixel_put(state, i, j, YELLOW);
		}
	}

	for (double i = 0; i < state->fov; i += state->ray_offset) {
		cast_ray(state, state->px, state->py, state->pa + i - state->fov/2, RED);
	}
}

int set_player_pos(int x, int y) {
	if (x >= 0 && x < state.map_length * mapS
		&& y >= 0 && y < state.map_height * mapS
		&& !is_wall(x, y)
	) {
		state.px = x;
		state.py = y;
		return 1;
	}
	return 0;
}
