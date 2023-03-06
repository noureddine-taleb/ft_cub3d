#include "cub3d.h"

void draw_sprite() {
	struct sprite *sprite = &state.sprite;
	double sx = sprite->sx - state.__px;
	double sy = sprite->sy - state.__py;
	double sz = 5;

	rotate(&sx, &sy, -state.__pa);
	double dist = dist_from_origin(sx, sy);
	double pixel_per_step = (WIDTH) / (state.__fov * dist);
	if (sx < 0)
		return;
	sx = sy * pixel_per_step + (WIDTH/2);
	sy = sz * pixel_per_step + (HEIGHT/2);

	if (sx < 0 || sy < 0 || sx > WIDTH || sy > HEIGHT)
		return;

	if (state.__zbuffer[(int)(sx / state.__line_thickness)].dist < dist)
		return;

	if (dist <= 0)
		return;

	double height = sprite->img_attr.height * 30 / dist;
	double width = sprite->img_attr.width * 30 / dist;
	double startx = sx - width/2;
	double starty = sy - height/2;
	double dy = sprite->img_attr.height / height;
	double dx = sprite->img_attr.width / width;
	double tx = 0;
	double ty = 0;
	for (int x = startx; x < startx + width && tx < sprite->img_attr.width; x++, tx += dx) {
		if (x < 0 || x >= WIDTH)
			continue;
		ty = 0;
		for (int y = starty; y < starty + height && y < HEIGHT && ty < sprite->img_attr.height; y++, ty += dy) {
			buffered_pixel_put(x, y, img_pixel_read(&sprite->img_attr, tx, ty));
		}
	}
}
