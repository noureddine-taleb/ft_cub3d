#include "cub3d.h"

// this files contains routines that aid in debug hence they should not be on production

// TODO: delete this
void	print_state(t_state *state)
{
	printf("map_height: %d\n", state->map_height);
	printf("map_width: %d\n", state->map_width);
	for (int i=0; i < state->map_height; i++) {
		for (int j = 0; j < state->map_width; j++) {
			printf("%c", __map(state, j, i));
		}
		printf("\n");
	}
	printf("px: %d\n", state->px);
	printf("py: %d\n", state->py);
	printf("north_texture: %s\n", state->north_texture.path);
	printf("south_texture: %s\n", state->south_texture.path);
	printf("east_texture: %s\n", state->east_texture.path);
	printf("west_texture: %s\n", state->west_texture.path);
	printf("sprite: %s\n", state->sprite.path);
	printf("f: %d\n", state->f);
	printf("c: %d\n", state->c);
	printf("elem: %d\n", state->elem);
	printf("flag: %d\n", state->flag);
}

// TODO: delete this
void	parser_stub(t_state *state)
{
	state->map_width = 8;
	state->door_texture.path = "./assets/door2.xpm";
	state->sprite.path = "./assets/mushroom_cloud.xpm";
	state->sprite.sy = 2;
	state->sprite.sx = 3;
	state->sprite.__sz = 5;
	state->sprite.rows = 4;
	state->sprite.cols = 5;
	print_state(state);
}

void	print_sprite(t_state *state)
{
	printf("path = %s\n", state->sprite.path);
	printf("img_attr.width = %d\n", state->sprite.img_attr.width);
	printf("img_attr.height = %d\n", state->sprite.img_attr.height);
	printf("__unit_width = %d\n", state->sprite.__unit_width);
	printf("__unit_height = %d\n", state->sprite.__unit_height);
	printf("sx = %d\n", state->sprite.sx);
	printf("sy = %d\n", state->sprite.sy);
	printf("cols = %d\n", state->sprite.cols);
	printf("rows = %d\n", state->sprite.rows);
	printf("__x_off = %d\n", state->sprite.__x_off);
	printf("__y_off = %d\n", state->sprite.__y_off);
	printf("__sx = %d\n", state->sprite.__sx);
	printf("__sy = %d\n", state->sprite.__sy);
	printf("__sz = %d\n\n", state->sprite.__sz);
}

// TODO: remove me
void	buffered_img_put(t_state *state, t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->width)
	{
		j = 0;
		while (j < img->height)
		{
			buffered_pixel_put(state, (t_point){i, j},
				img_pixel_read(img, i, j));
			j++;
		}
		i++;
	}
}

// TODO: remove me
void	buffered_sprite_put(t_state *state, struct s_sprite *sprite)
{
	for (int i = 0; i < sprite->__unit_width; i++) {
		for (int j = 0; j < sprite->__unit_height; j++) {
			buffered_pixel_put(state, (t_point){i, j},
				img_pixel_read(&sprite->img_attr, sprite->__x_off + i, sprite->__y_off + j));
		}
	}
}
