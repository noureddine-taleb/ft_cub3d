#include "cub3d.h"

int	img_pixel_read(struct texture *t, int x, int y) {
	char	*dst;

	if (x >= t->width || y >= t->height)
		return 0;
	dst = t->img + (y * t->width * 4 + x * (4));
	return *(unsigned int *)dst;
}

void read_texture(struct texture *t) {
	// TODO: verify texture dimensions
	int dummy;
	// void *mlx = mlx_init(); // TODO: this probably needs to be freed
	t->img = mlx_xpm_file_to_image(state.mlx, t->path, &t->width, &t->height);
	printf("done opening xpm file\n");
	if (!t->img) {
		printf("can't open texture img\n");
		exit(1);
	}
	t->img = mlx_get_data_addr(t->img, &dummy, &dummy, &dummy);
}
