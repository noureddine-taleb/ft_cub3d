#include "cub3d.h"

void draw_map_pixel(t_state *_state, int x, int y) {
	for (int j = mapY(y); j < mapY(y) + mapS; j++) {
		for (int i = mapX(x); i < mapX(x) + mapS; i++) {
			buffered_pixel_put(_state, i, j, MAP[y][x]);
		}
	}
}

void draw_ray(double x, double y, double angle, int color) {
	double dx = cos(angle);
	double dy = sin(angle);

	while (!is_wall(x, y)) {
		buffered_pixel_put(&state, x, y, color);
		x += dx;
		y += dy;
	}
}

void draw_map(t_state *state) {
	// draw map
	for (int j = 0; j < state->map_height; j++) {
		for (int i = 0; i < state->map_length; i++) {
			draw_map_pixel(state, i, j);
		}
	}

	// draw player
	for (int j = state->py; j < state->py + pS; j++) {
		for (int i = state->px; i < state->px + pS; i++) {
			buffered_pixel_put(state, i, j, YELLOW);
		}
	}

	// draw rays
	for (double ra = state->pa - state->fov/2; ra < state->pa + state->fov/2; ra += state->ray_offset) {
		draw_ray(state->px + pS/2, state->py + pS/2, ra, RED);
	}
}

enum wall_orientation is_wall(int x, int y) {
	x /= mapS;
	y /= mapS;

	if (!(x >= 0 && x < state.map_length
		&& y >= 0 && y < state.map_height))
		return -1;
	if (IS_WALL(MAP[y][x])) {
		return 1;
	}
	return 0;
}
