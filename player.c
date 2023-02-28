#include "cub3d.h"

#define pS 8

// double dist(int ax, int ay, int bx, int by) {

// }

void draw_ray(double x, double y, double angle, int color) {
	double dx = cos(angle);
	double dy = sin(angle);

	while (!is_wall(x, y)) {
		buffered_pixel_put(&state, x, y, color);
		x += dx;
		y += dy;
	}
}

double cast_ray(t_state *state, const int x0, const int y0, const double angle, int color, enum wall_orientation *orientation) {
	double vDist = 0;
	double hDist = 0;
	double m = tan(angle); // like in y=mx
	int rx = 0;
	int ry = 0;
	
	// calc vertical dist
	if (sin(angle) < 0) { // up
		ry = -(y0 % mapS) - 1;
		rx = ry / m;
	} else if (sin(angle) > 0) { // down
		ry = mapS - (y0 % mapS);
		rx = ry / m;
	}
	if (sin(angle)) {
		while (
			!is_wall(rx + x0, ry + y0)
			) {
			if (sin(angle) < 0) {
				ry -= mapS;
				rx = ry / m;
			} else if (sin(angle) > 0) {
				ry += mapS;
				rx = ry / m;
			}
		}
		vDist = sqrt(rx*rx + ry*ry);
	} else {
		vDist = INFINITY;
	}

	// calc horizontal dist
	rx = ry = 0;
	if (cos(angle) < 0) { // left
		rx = -(x0 % mapS) - 1;
		ry = m * rx;
	} else if (cos(angle) > 0) { // right
		rx = mapS - (x0 % mapS);
		ry = m * rx;
	}
	if (cos(angle)) {
		while (!is_wall(rx + x0, ry + y0)) {
			if (cos(angle) < 0) { // left
				rx -= mapS;
				ry = m * rx;
			} else if (cos(angle) > 0) { // right
				rx += mapS;
				ry = m * rx;
			}
		}
		hDist = sqrt(rx*rx + ry*ry);
	} else {
		hDist = INFINITY;
	}

	double dist = (vDist > hDist ? ({ *orientation = w_horizontal; hDist; }) : ({ *orientation = w_vertical; vDist; }));
	draw_ray(x0, y0, angle, color);
	return dist;
}

int line = 0; // TODO: to be removed

void draw_3dline(int i, double dist, double ra, int color) {
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
