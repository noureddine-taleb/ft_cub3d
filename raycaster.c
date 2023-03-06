#include "cub3d.h"

#define NORTH(angle) (sin(angle) < 0)
#define SOUTH(angle) (sin(angle) > 0)
#define EAST(angle) (cos(angle) > 0)
#define WEST(angle) (cos(angle) < 0)

static double dist_to_wall_size(double dist, double ra) {
	dist = dist * cos(state.__pa - ra); // fix fisheye effect
	dist = (HEIGHT*20) / dist;
	return dist;
}

static struct ray_intersection cast_ray_vertical(double angle) {
	struct ray_intersection intersection = { .angle = angle };
	double m = tan(angle); // like in y=mx
	const int x0 = state.__px;
	const int y0 = state.__py;

	intersection.orientation = horizontal;
	if (NORTH(angle)) {
		intersection.y = -(y0 % mapS) - 1;
		intersection.x = intersection.y / m;
	} else if (SOUTH(angle)) {
		intersection.y = mapS - (y0 % mapS);
		intersection.x = intersection.y / m;
	}
	if (sin(angle)) {
		while (map_terrain(intersection.x + x0, intersection.y + y0) == terrain_positive_space) {
			if (NORTH(angle)) {
				intersection.y -= mapS;
				intersection.x = intersection.y / m;
			} else if (SOUTH(angle)) {
				intersection.y += mapS;
				intersection.x = intersection.y / m;
			}
		}
		intersection.dist = dist_from_origin(intersection.x, intersection.y);
		intersection.x += x0;
		intersection.y += y0;
	} else {
		intersection.dist = INFINITY;
	}
	return intersection;
}

static struct ray_intersection cast_ray_horizontal(double angle) {
	struct ray_intersection intersection = { .angle = angle };
	double m = tan(angle); // like in y=mx
	const int x0 = state.__px;
	const int y0 = state.__py;

	intersection.orientation = vertical;
	if (WEST(angle)) {
		intersection.x = -(x0 % mapS) - 1;
		intersection.y = m * intersection.x;
	} else if (EAST(angle)) {
		intersection.x = mapS - (x0 % mapS);
		intersection.y = m * intersection.x;
	}
	if (cos(angle)) {
		while (map_terrain(intersection.x + x0, intersection.y + y0) == terrain_positive_space) {
			if (WEST(angle)) {
				intersection.x -= mapS;
				intersection.y = m * intersection.x;
			} else if (EAST(angle)) {
				intersection.x += mapS;
				intersection.y = m * intersection.x;
			}
		}
		intersection.dist = dist_from_origin(intersection.x, intersection.y);
		intersection.x += x0;
		intersection.y += y0;
	} else {
		intersection.dist = INFINITY;
	}
	return intersection;
}

static void cast_ray(struct ray_intersection *intersection) {
	struct ray_intersection v = cast_ray_vertical(intersection->angle);
	struct ray_intersection h = cast_ray_horizontal(intersection->angle);

	if (v.dist < h.dist)
		*intersection = v;
	else
		*intersection = h;
}

static struct texture *get_texture(struct ray_intersection *intersection) {
	if (NORTH(intersection->angle) && intersection->orientation == horizontal)
		return &state.north_texture;
	else if (EAST(intersection->angle) && intersection->orientation == vertical)
		return &state.east_texture;
	else if (SOUTH(intersection->angle) && intersection->orientation == horizontal)
		return &state.south_texture;
	else if (WEST(intersection->angle) && intersection->orientation == vertical)
		return &state.west_texture;
	die("can't find appropriate texture for the intersection point");
	return NULL; // unreachable anyway
}

static void draw_horizontal_line(int i) {
	struct ray_intersection *intersection = &state.__zbuffer[i];
	t_img *texture = &get_texture(intersection)->img_attr;

	if (i >= state.__line_count)
		return;

	double len = dist_to_wall_size(intersection->dist, intersection->angle);
	int startx = i * state.__line_thickness;
	int starty = (HEIGHT/2) - len/2;
	double initTextureY = 0;
	double stepy = (double)texture->height / len;
	if (starty < 0) {
		initTextureY = -starty * stepy;
		starty = 0;
	}
	// sky or ceiling
	for (int col = startx; col < startx + state.__line_thickness; col++) {
		for (int row = 0; row < starty; row++) {
			buffered_pixel_put(col, row, state.c);
		}
	}
	// walls
	int x;
	if (intersection->orientation == vertical)
		x = intersection->y % (mapS) / (double)mapS * texture->width;
	else
		x = intersection->x % (mapS) / (double)mapS * texture->width;
	double y;
	for (int col = startx; col < startx + state.__line_thickness; col++) {
		y = initTextureY;
		for (int row = starty; (row < starty + len) && row < HEIGHT; row++, y+=stepy) {
			buffered_pixel_put(col, row, img_pixel_read(texture, x, y));
		}
	}
	// ground
	for (int col = startx; col < (startx + state.__line_thickness) && col >= 0 && col < WIDTH; col++) {
		for (int row = starty + len; row >= 0 && row < HEIGHT; row++) {
			buffered_pixel_put(col, row, state.f);
		}
	}
}

void raycasting() {
	int i = 0;

	for (double ra = state.__pa - state.__fov/2; ra < state.__pa + state.__fov/2; ra += state.__ray_offset, i++) {
		state.__zbuffer[i].angle = ra;
		cast_ray(&state.__zbuffer[i]);
		draw_horizontal_line(i);
	}
}
