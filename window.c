/**
 * initialise the screen
 * bind keyboard events (arrow keys)
 * call the render function when necessary
*/
#include "cub3d.h"

void	init_frame(t_state *vars, t_frame *f)
{
	int scratch;
	f->img_attr.width = WIDTH;
	f->img_attr.height = HEIGHT;
	f->img_attr.img = mlx_new_image(vars->__mlx, WIDTH, HEIGHT);
	f->img_attr.addr = mlx_get_data_addr(f->img_attr.img, &scratch, &scratch, &scratch);
}

int	destroy(t_state *state)
{
	mlx_destroy_image(state->__mlx, state->__frame.img_attr.img);
	mlx_destroy_window(state->__mlx, state->__win);
	exit(0);
}

int key_press(int keycode, t_state *state) {
	switch (keycode)
	{
	case KEY_LEFT:
		state->__pa -= 0.1;
		break;

	case KEY_RIGHT:
		state->__pa += 0.1;
		break;

	case KEY_UP:
	case KEY_W:
		set_player_pos(state->__px + cos(state->__pa) * 5, state->__py + sin(state->__pa) * 5);
		break;

	case KEY_DOWN:
	case KEY_S:
		set_player_pos(state->__px - cos(state->__pa) * 5, state->__py - sin(state->__pa) * 5);
		break;

	case KEY_A:
		set_player_pos(state->__px + cos(state->__pa - M_PI/2) * 5, state->__py + sin(state->__pa - M_PI/2) * 5);
		break;

	case KEY_D:
		set_player_pos(state->__px + cos(state->__pa + M_PI/2) * 5, state->__py + sin(state->__pa + M_PI/2) * 5);
		break;
	
	case KEY_ESC:
		destroy(state);
		break;
	}
	render(state);
	return 0;
}

int mouse_event(int mousecode, int x, int y, t_state *state) {
	switch (mousecode)
	{
	case MOUSE_LEFT:
		set_player_pos(x, y);
		break;
	
	case MOUSE_SCROLL_UP:
		state->__pa += 0.1;
		break;
	
	case MOUSE_SCROLL_DOWN:
		state->__pa -= 0.1;
		break;
	}
	render(state);
	return 0;
}

void init_window() {
	state.__mlx = mlx_init();
	init_frame(&state, &state.__frame);
	state.__win = mlx_new_window(state.__mlx, WIDTH, HEIGHT, "cub3d");
	mlx_key_hook(state.__win, key_press, &state);
	mlx_mouse_hook(state.__win, mouse_event, &state);
	mlx_hook(state.__win, ON_DESTROY, 0, destroy, &state);
}

void	buffered_pixel_put(int x, int y, unsigned int color)
{
	char	*dst;
	t_img *frame_img;

	frame_img = &state.__frame.img_attr;
	if (color & 0xff000000)
		return;
	dst = frame_img->addr + ((y * frame_img->width + x) * 4);
	*(unsigned int *)dst = color;
}

void read_img_from_xpm(char *xpm, t_img *img) {
	int dummy;
	img->img = mlx_xpm_file_to_image(state.__mlx, xpm, &img->width, &img->height);
	if (!img->img)
		die("can't open the img file");
	img->addr = mlx_get_data_addr(img->img, &dummy, &dummy, &dummy);
}

int	img_pixel_read(t_img *img, int x, int y) {
	char	*dst;

	dst = img->addr + (y * img->width + x) * 4;
	return *(unsigned int *)dst;
}

void	flush_frame()
{
	mlx_put_image_to_window(state.__mlx, state.__win, state.__frame.img_attr.img, 0, 0);
}

void reset_frame() {
	#include <string.h>
	t_img *frame_img;

	frame_img = &state.__frame.img_attr;
	memset(state.__frame.img_attr.addr, 0, frame_img->width * frame_img->height * 4); // TODO: to remove
}

int	render()
{
	reset_frame();
	draw_frame();
	flush_frame();
	return (0);
}
