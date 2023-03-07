#include "cub3d.h"

void die(char *msg) {
	perror(msg);
	exit(1);
}

void flip_sprite_state();
void print_sprite();

void buffered_img_put(t_img *img) {
	for (int i = 0; i < img->width; i++)
		for (int j = 0; j < img->height; j++) {
			buffered_pixel_put(i, j, img_pixel_read(img, i, j));
		}
}

void buffered_sprite_put(struct sprite *sprite) {
	for (int i = 0; i < sprite->__unit_width; i++) {
		for (int j = 0; j < sprite->__unit_height; j++) {
			buffered_pixel_put(i, j, img_pixel_read(&sprite->img_attr, sprite->__x_off + i, sprite->__y_off + j));
		}
	}
}

void draw_frame() {
	// buffered_sprite_put(&state.sprite);
	// flip_sprite_state();
	raycasting();
	draw_sprite();
	draw_map();
}
