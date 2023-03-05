#include "cub3d.h"

int	img_pixel_read(struct texture *t, int x, int y) {
	char	*dst;

	if (x >= t->width || y >= t->height)
		return 0;
	dst = t->img + (y * t->width * 4 + x * (4));
	return *(unsigned int *)dst;
}

void read_texture(struct texture *t) {
	int dummy;
	t->img = mlx_xpm_file_to_image(state.__mlx, t->path, &t->width, &t->height);
	if (!t->img)
		die("can't open texture img");
	t->img = mlx_get_data_addr(t->img, &dummy, &dummy, &dummy);
}

void read_sprite(struct sprite *t) {
	int dummy;
	t->img = mlx_xpm_file_to_image(state.__mlx, t->path, &t->width, &t->height);
	if (!t->img)
		die("can't open texture img");
	t->img = mlx_get_data_addr(t->img, &dummy, &dummy, &dummy);
}
