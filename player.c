#include "cub3d.h"

#define pS 8

double cast_ray(t_state *state, int x, int y, double angle, int color, enum wall_orientation *orientation) {
	double dx = cos(angle);
	double dy = sin(angle);
	double rx = x;
	double ry = y;
	double x0 = x;
	double y0 = y;

	while (
		ry >= 0 && ry < state->map_height * mapS
		&& rx >= 0 && rx < state->map_length * mapS
	) {
		if ((*orientation = is_wall(rx, ry)))
			break;
		buffered_pixel_put(state, rx, ry, color);
		rx += dx;
		ry += dy;
	}
	return (sqrt(pow(rx-x0, 2) + pow(ry-y0, 2)));
}

int line = 0; // TODO: to be removed

void draw_3dline(int i, int dist, double ra, int color) {
	int line_count = state.fov / state.ray_offset;
	int line_thickness = WIDTH / line_count; // TOOP cache repeated calcs

	if (i >= line_count)
		return;

	dist = dist * cos(state.pa - ra); // fix fisheye effect
	dist = (HEIGHT*20) / dist;
	if (dist > HEIGHT)
		dist = HEIGHT;

	int startx = i * line_thickness;
	for (int col = 0; col < line_thickness; col++) {
		for (int row = 0; row < dist; row++) {
			buffered_pixel_put(&state, startx + col, (HEIGHT/2) - dist/2 + row, color);
		}
	}
}

void draw_player(t_state *state) {
	for (int j = state->py; j < state->py + pS; j++) {
		for (int i = state->px; i < state->px + pS; i++) {
			buffered_pixel_put(state, i, j, YELLOW);
		}
	}

	line = 0;
	enum wall_orientation orientation;
	for (double i = 0; i < state->fov; i += state->ray_offset) {
		double ra = state->pa + i - state->fov/2;
		int dist = cast_ray(state, state->px + pS/2, state->py + pS/2, ra, RED, &orientation);
		if (orientation == w_horizontal)
			draw_3dline(line, dist, ra, GREEN);
		else if (orientation == w_vertical)
			draw_3dline(line, dist, ra, GREEN_DARK);
		line++;
	}
}

int set_player_pos(int x, int y) {
	if (x >= 0 && x < state.map_length * mapS
		&& y >= 0 && y < state.map_height * mapS
		&& is_wall(x, y) == w_out
	) {
		state.px = x;
		state.py = y;
		return 1;
	}
	return 0;
}
