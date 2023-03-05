#include "cub3d.h"

void draw_map_pixel(int x, int y) {
	for (int j = mapY(y); j < mapY(y) + mapS; j++) {
		for (int i = mapX(x); i < mapX(x) + mapS; i++) {
			if (__IS_WALL(x, y))
				buffered_pixel_put(i, j, WHITE);
			else
				buffered_pixel_put(i, j, BLACK);
		}
	}
}

void draw_ray(double x, double y, double angle, int color) {
	double dx = cos(angle);
	double dy = sin(angle);

	while (map_terrain(x, y) == terrain_positive_space) {
		buffered_pixel_put(x, y, color);
		x += dx;
		y += dy;
	}
}

enum terrain map_terrain(int x, int y) {
	x /= mapS;
	y /= mapS;

	if (__IS_EMPTY(x, y))
		return terrain_negative_space;

	if (__IS_WALL(x, y))
		return terrain_wall;

	return terrain_positive_space;
}

void draw_map() {
	// draw map
	for (int j = 0; j < state.map_height; j++) {
		for (int i = 0; i < state.map_width; i++) {
			draw_map_pixel(i, j);
		}
	}

	// draw player
	for (int j = state.__py; j < state.__py + pS; j++) {
		for (int i = state.__px; i < state.__px + pS; i++) {
			buffered_pixel_put(i, j, YELLOW);
		}
	}

	// draw rays
	for (double ra = state.__pa - state.__fov/2; ra < state.__pa + state.__fov/2; ra += state.__ray_offset) {
		draw_ray(state.__px + pS/2, state.__py + pS/2, ra, RED);
	}

	// draw sprite
	for (int j = state.sprite.__sy; j < state.sprite.__sy + pS; j++) {
		for (int i = state.sprite.__sx; i < state.sprite.__sx + pS; i++) {
			buffered_pixel_put(i, j, GREEN);
		}
	}
}
