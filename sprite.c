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

void __draw_sprite(double sx, double sy, double dist) {
	t_img *sprite = &state.sprite.img_attr;

	double height = sprite->height * 30 / dist;
	double width = sprite->width * 30 / dist;
	// window
	double startwx = sx - width/2;
	double startwy = sy - height/2;
	// texture
	double tx = 0;
	double ty = 0;
	double dty = sprite->height / height;
	double dtx = sprite->width / width;

	for (int wx = startwx; wx < startwx + width; wx++, tx += dtx) {
		ty = 0;
		for (int wy = startwy; wy < startwy + height; wy++, ty += dty) {
			buffered_pixel_put(wx, wy, img_pixel_read(sprite, tx, ty));
		}
	}
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
