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
		while (map_terrain(intersection.x + x0, intersection.y + y0) == terrain_positive_space
			|| (map_terrain(intersection.x + x0, intersection.y + y0) == terrain_door && dist_from_origin(intersection.x, intersection.y) <= (mapS))
		) {
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
		while (map_terrain(intersection.x + x0, intersection.y + y0) == terrain_positive_space
			|| (map_terrain(intersection.x + x0, intersection.y + y0) == terrain_door && dist_from_origin(intersection.x, intersection.y) <= (mapS*2))
		) {
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

static void draw_wall(struct ray_intersection *intersection, double height, int startwx, int startwy) {
	t_img *wall_texture = &get_texture(intersection)->img_attr;
	double dty = (double)wall_texture->height / height;

	double tx;
	if (intersection->orientation == vertical)
		tx = intersection->y % (mapS) / (double)mapS * wall_texture->width;
	else
		tx = intersection->x % (mapS) / (double)mapS * wall_texture->width;
	double ty;
	for (int wx = startwx; wx < startwx + state.__line_thickness; wx++) {
		ty = 0;
		for (int wy = startwy; wy < startwy + height; wy++, ty += dty) {
			buffered_pixel_put(wx, wy, img_pixel_read(wall_texture, tx, ty));
		}
	}
}

static void draw_bg(double height, int startwx, int startwy) {
	// sky or ceiling
	for (int wx = startwx; wx < startwx + state.__line_thickness; wx++) {
		for (int wy = 0; wy < startwy; wy++) {
			buffered_pixel_put(wx, wy, state.c);
		}
	}
	// ground
	for (int wx = startwx; wx < startwx + state.__line_thickness; wx++) {
		for (int wy = startwy + height; wy >= 0 && wy < HEIGHT; wy++) {
			buffered_pixel_put(wx, wy, state.f);
		}
	}
}

static void draw_horizontal_line(int i) {
	struct ray_intersection *intersection = &state.__zbuffer[i];

	if (i <0 || i >= state.__line_count)
		return;

	double height = dist_to_wall_size(intersection->dist, intersection->angle);
	int startwx = i * state.__line_thickness;
	int startwy = (HEIGHT/2) - height/2;
	draw_bg(height, startwx, startwy);
	draw_wall(intersection, height, startwx, startwy);
}

void raycasting() {
	int i = 0;

	for (double ra = state.__pa - state.__fov/2; ra < state.__pa + state.__fov/2; ra += state.__ray_offset, i++) {
		state.__zbuffer[i].angle = ra;
		cast_ray(&state.__zbuffer[i]);
		draw_horizontal_line(i);
	}
}
