#include "cub3d.h"

int	sprite_pixel_read(struct sprite *t, int x, int y) {
	char	*dst;

	dst = t->img + (y * t->width * 4 + x * (4));
	return *(unsigned int *)dst;
}

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

	double height = sprite->height * 30 / dist;
	double width = sprite->width * 30 / dist;
	double startx = sx - width/2;
	double starty = sy - height/2;
	double dy = sprite->height / height;
	double dx = sprite->width / width;
	double tx = 0;
	double ty = 0;
	for (int x = startx; x < startx + width && tx < sprite->width; x++, tx += dx) {
		if (x < 0 || x >= WIDTH)
			continue;
		ty = 0;
		for (int y = starty; y < starty + height && y < HEIGHT && ty < sprite->height; y++, ty += dy) {
			buffered_pixel_put(x, y, sprite_pixel_read(sprite, tx, ty));
		}
	}
}
