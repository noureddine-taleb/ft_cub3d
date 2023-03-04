#include "cub3d.h"

double dist_from_origin(int x, int y) {
	return sqrt(x*x + y*y);
}

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
			if (is_monster(rx + x0, ry + y0))
				state->monster_sprite.dist = sqrt(rx*rx + ry*ry);
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
			if (is_monster(rx + x0, ry + y0) && state->monster_sprite.dist > sqrt(rx*rx + ry*ry))
				state->monster_sprite.dist = sqrt(rx*rx + ry*ry);

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

double dist_to_wall_size(double dist, double ra) {
	dist = dist * cos(state.pa - ra); // fix fisheye effect
	dist = (HEIGHT*20) / dist;
	return dist;
}

void draw_3dline(int i, double dist, double ra, enum wall_orientation orientation, int ix, int iy) {
	
	if (i >= state.__line_count)
		return;

	dist = dist_to_wall_size(dist, ra);

	int startx = i * state.__line_thickness;
	int starty = (HEIGHT/2) - dist/2;
	double initTextureY = 0;
	double stepy = (double)state.wall_texture.height / dist;
	if (starty < 0) {
		initTextureY = -starty * stepy;
		starty = 0;
	}
	// sky or ceiling
	for (int col = startx; col < startx + state.__line_thickness; col++) {
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
	for (int col = startx; col < startx + state.__line_thickness; col++) {
		y = initTextureY;
		for (int row = starty; (row < starty + dist) && row < HEIGHT; row++, y+=stepy) {
			buffered_pixel_put(&state, col, row, img_pixel_read(&state.wall_texture, x, y));
			// buffered_pixel_put(&state, col, row, color);
		}
	}
	// ground
	for (int col = startx; col < (startx + state.__line_thickness) && col >= 0 && col < WIDTH; col++) {
		for (int row = starty + dist; row >= 0 && row < HEIGHT; row++) {
			buffered_pixel_put(&state, col, row, COLOR(0x00, 0xc0, 0xc0, 0xc0));
		}
	}
}

int	sprite_pixel_read(struct sprite *t, int x, int y) {
	char	*dst;

	dst = t->img + (y * t->width * 4 + x * (4));
	return *(unsigned int *)dst;
}

void rotate(double *x, double *y, double angle) {
	double _sin = sin(-state.pa);
	double _cos = cos(-state.pa);

	double a = *x * _cos - *y * _sin;
	double b = *x * _sin + *y * _cos;
	*x = a;
	*y = b;
}

void draw_sprite() {
	struct sprite *monster = &state.monster_sprite;
	double sx = monster->mx - state.px;
	double sy = monster->my - state.py;
	double sz = 5;

	rotate(&sx, &sy, -state.pa);
	double dist = dist_from_origin(sx, sy);
	double pixel_per_step = (WIDTH) / (state.fov * dist);
	if (sx < 0)
		return;
	sx = sy * pixel_per_step + (WIDTH/2);
	sy = sz * pixel_per_step + (HEIGHT/2);

	if (sx < 0 || sy < 0 || sx > WIDTH || sy > HEIGHT)
		return;

	if (state.zbuffer[(int)(sx / state.__line_thickness)] < dist)
		return;

	if (dist <= 0)
		return;

	double height = monster->height * 30 / dist;
	double width = monster->width * 30 / dist;
	double startx = sx - width/2;
	double starty = sy - height/2;
	double dy = monster->height / height;
	double dx = monster->width / width;
	double tx = 0;
	double ty = 0;
	for (int x = startx; x < startx + width && tx < monster->width; x++, tx += dx) {
		if (x < 0 || x >= WIDTH)
			continue;
		ty = 0;
		for (int y = starty; y < starty + height && y < HEIGHT && ty < monster->height; y++, ty += dy) {
			buffered_pixel_put(&state, x, y, sprite_pixel_read(monster, tx, ty));
		}
	}
}

void draw_3dscene(t_state *state) {
	enum wall_orientation orientation;
	int ix, iy;
	int line = 0;
	for (double ra = state->pa - state->fov/2; ra < state->pa + state->fov/2; ra += state->ray_offset) {
		state->zbuffer[line] = cast_ray(state, state->px, state->py, ra, RED, &orientation, &ix, &iy);
		draw_3dline(line, state->zbuffer[line], ra, orientation, ix, iy);
		line++;
	}
	draw_sprite();
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
