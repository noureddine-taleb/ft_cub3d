/**
 * initialise the screen
 * bind keyboard events (arrow keys)
 * call the render function when necessary
*/
#include "cub3d.h"

void	init_frame(t_state *vars, t_frame *f)
{
	f->img = mlx_new_image(vars->__mlx, WIDTH, HEIGHT);
	f->addr = mlx_get_data_addr(f->img, &f->pixel_size, &f->line_size, &f->endian);
	f->pixel_size /= 8;
}

int	destroy(t_state *state)
{
	mlx_destroy_image(state->__mlx, state->__frame.img);
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

	if (color & 0xff000000)
		return;
	dst = state.__frame.addr + (y * state.__frame.line_size
			+ x * (state.__frame.pixel_size));
	*(unsigned int *)dst = color;
}

void	flush_frame()
{
	mlx_put_image_to_window(state.__mlx, state.__win, state.__frame.img, 0, 0);
}

void reset_frame() {
	#include <string.h>
	memset(state.__frame.addr, 0, state.__frame.line_size * HEIGHT); // TODO: to remove
}

int	render()
{
	reset_frame();
	draw_frame();
	flush_frame();
	return (0);
}
