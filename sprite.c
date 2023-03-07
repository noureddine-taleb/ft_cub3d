#include "cub3d.h"

int should_display_sprite(double sx, double sy, double dist) {
	if (sx < 0 || sy < 0 || sx >= WIDTH || sy >= HEIGHT)
		return 0;

	if (state.__zbuffer[(int)(sx / state.__line_thickness)].dist < dist)
		return 0;

	if (dist <= 0)
		return 0;
	
	return 1;
}

void print_sprite() {
	printf("path = %s\n", state.sprite.path);
	printf("img_attr.width = %d\n", state.sprite.img_attr.width);
	printf("img_attr.height = %d\n", state.sprite.img_attr.height);
	printf("__unit_width = %d\n", state.sprite.__unit_width);
	printf("__unit_height = %d\n", state.sprite.__unit_height);
	printf("sx = %d\n", state.sprite.sx);
	printf("sy = %d\n", state.sprite.sy);
	printf("cols = %d\n", state.sprite.cols);
	printf("rows = %d\n", state.sprite.rows);
	printf("__x_off = %d\n", state.sprite.__x_off);
	printf("__y_off = %d\n", state.sprite.__y_off);
	printf("__sx = %d\n", state.sprite.__sx);
	printf("__sy = %d\n", state.sprite.__sy);
	printf("__sz = %d\n\n", state.sprite.__sz);
}

void flip_sprite_state() {
	state.sprite.__x_off += state.sprite.__unit_width;
	if (state.sprite.__x_off >= state.sprite.img_attr.width) {
		state.sprite.__x_off = 0;
		state.sprite.__y_off += state.sprite.__unit_height;
		if (state.sprite.__y_off >= state.sprite.img_attr.height)
			state.sprite.__y_off = 0;
	}
}

void __draw_sprite(double sx, double sy, double dist) {
	struct sprite *sprite = &state.sprite;
	
	// print_sprite();
	
	double height = 30 * sprite->__unit_height / dist;
	double width = 30 * sprite->__unit_width / dist;
	// window
	double startwx = sx - width/2;
	double startwy = sy - height/2;
	// texture
	double tx = sprite->__x_off;
	double ty = sprite->__y_off;
	double dty = sprite->__unit_height / height;
	double dtx = sprite->__unit_width / width;

	double csx = sx;
	double csy = sy;

	for (int wx = startwx; wx < startwx + width; wx++, tx += dtx) {
		ty = sprite->__y_off;
		for (int wy = startwy; wy < startwy + height; wy++, ty += dty) {
			buffered_pixel_put(wx, wy, img_pixel_read(&sprite->img_attr, tx, ty));
		}
	}
	flip_sprite_state();
}

void draw_sprite() {
	struct sprite *sprite = &state.sprite;
	double sx = sprite->__sx - state.__px;
	double sy = sprite->__sy - state.__py;
	double sz = sprite->__sz;

	rotate(&sx, &sy, -state.__pa);
	double dist = dist_from_origin(sx, sy);
	double pixels_per_fov = WIDTH / (state.__fov * dist);
	if (sx < 0)
		return;
	sx = sy * pixels_per_fov + (WIDTH/2);
	sy = sz * pixels_per_fov + (HEIGHT/2);

	if (should_display_sprite(sx, sy, dist))
		__draw_sprite(sx, sy, dist);
}
