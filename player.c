#include "cub3d.h"

// double dist(int ax, int ay, int bx, int by) {

// }

double cast_ray(t_state *state, const int x0, const int y0, const double angle, int color, enum wall_orientation *orientation, int *ix, int *iy) {
	double vDist = 0;
	double hDist = 0;
	double m = tan(angle); // like in y=mx
	int rx = 0;
	int ry = 0;

	int vix;
	int hix;
	int viy;
	int hiy;
	
	// calc vertical dist
	if (sin(angle) < 0) { // up
		ry = -(y0 % mapS) - 1;
		rx = ry / m;
	} else if (sin(angle) > 0) { // down
		ry = mapS - (y0 % mapS);
		rx = ry / m;
	}
	if (sin(angle)) {
		while (!is_wall(rx + x0, ry + y0)) {
			if (sin(angle) < 0) {
				ry -= mapS;
				rx = ry / m;
			} else if (sin(angle) > 0) {
				ry += mapS;
				rx = ry / m;
			}
		}
		vDist = sqrt(rx*rx + ry*ry);
		vix = rx + x0, viy = ry + y0;
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
		hix = rx + x0, hiy = ry + y0;
	} else {
		hDist = INFINITY;
	}

	double dist = (vDist > hDist ? ({ *orientation = w_vertical; *ix = hix, *iy = hiy, hDist; }) : ({ *orientation = w_horizontal; *ix = vix, *iy = viy, vDist; }));
	// draw_ray(x0, y0, angle, color);
	return dist;
}

int line = 0; // TODO: to be removed

double dist_to_wall_size(double dist, double ra) {
	dist = dist * cos(state.pa - ra); // fix fisheye effect
	dist = (HEIGHT*20) / dist;
	return dist;
}

void draw_3dline(int i, double dist, double ra, enum wall_orientation orientation, int ix, int iy) {
	int line_count = state.fov / state.ray_offset;
	int line_thickness = WIDTH / line_count; // TOOP cache repeated calcs
	
	if (i >= line_count)
		return;

	dist = dist_to_wall_size(dist, ra);

	int startx = i * line_thickness;
	int starty = (HEIGHT/2) - dist/2;
	double initTextureY = 0;
	double stepy = (double)state.wall_texture.height / dist;
	if (starty < 0) {
		initTextureY = -starty * stepy;
		starty = 0;
	}
	// sky or ceiling
	for (int col = startx; col < startx + line_thickness; col++) {
		for (int row = 0; row < starty; row++) {
			buffered_pixel_put(&state, col, row, COLOR(0x00, 0x66, 0xb2, 0xff));
		}
	}
	// walls
	int x;
	if (orientation == w_vertical)
		x = iy % (mapS) / (double)mapS * state.wall_texture.width;
	else
		x = ix % (mapS) / (double)mapS * state.wall_texture.width;
	double y;
	for (int col = startx; col < startx + line_thickness; col++) {
		y = initTextureY;
		for (int row = starty; (row < starty + dist) && row < HEIGHT; row++, y+=stepy) {
			buffered_pixel_put(&state, col, row, img_pixel_read(&state.wall_texture, x, y));
			// buffered_pixel_put(&state, col, row, color);
		}
	}
	// ground
	for (int col = startx; col < startx + line_thickness; col++) {
		for (int row = starty + dist; row < HEIGHT; row++) {
			buffered_pixel_put(&state, col, row, COLOR(0x00, 0xc0, 0xc0, 0xc0));
		}
	}
}

void draw_3dscene(t_state *state) {
	line = 0;
	enum wall_orientation orientation;
	int ix, iy;
	for (double i = 0; i < state->fov; i += state->ray_offset) {
		double ra = state->pa + i - state->fov/2;
		int dist = cast_ray(state, state->px, state->py, ra, RED, &orientation, &ix, &iy);
		draw_3dline(line, dist, ra, orientation, ix, iy);
		line++;
	}
}

int set_player_pos(int x, int y) {
	if (
		x >= 0 && x < state.map_length * mapS
		&& is_wall(x, state.py) == w_out
	)
		state.px = x;

	if (
		y >= 0 && y < state.map_height * mapS
		&& is_wall(state.px, y) == w_out
	)
		state.py = y;

	return 0;
}
