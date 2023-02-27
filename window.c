/**
 * initialise the screen
 * bind keyboard events (arrow keys)
 * call the render function when necessary
*/
#include "cub3d.h"

void	init_frame(t_state *vars, t_frame *f)
{
	f->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	f->addr = mlx_get_data_addr(f->img, &f->pixel_size, &f->line_size, &f->endian);
	f->pixel_size /= 8;
}

int	destroy(t_state *state)
{
	mlx_destroy_image(state->mlx, state->frame.img);
	mlx_destroy_window(state->mlx, state->win);
	exit(0);
}

int key_press(int keycode, t_state *state) {
	switch (keycode)
	{
	case KEY_LEFT:
		state->pa -= 0.1;
		break;

	case KEY_RIGHT:
		state->pa += 0.1;
		break;

	case KEY_UP:
		set_player_pos(state->px + cos(state->pa) * 5, state->py + sin(state->pa) * 5);
		break;

	case KEY_DOWN:
		set_player_pos(state->px - cos(state->pa) * 5, state->py - sin(state->pa) * 5);
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
		state->pa += 0.1;
		break;
	
	case MOUSE_SCROLL_DOWN:
		state->pa -= 0.1;
		break;
	}
	render(state);
	return 0;
}

void init_window() {
	state.mlx = mlx_init();
	init_frame(&state, &state.frame);
	state.win = mlx_new_window(state.mlx, WIDTH, HEIGHT, "cub3d");
	mlx_key_hook(state.win, key_press, &state);
	mlx_mouse_hook(state.win, mouse_event, &state);
	mlx_hook(state.win, ON_DESTROY, 0, destroy, &state);
}

void	buffered_pixel_put(t_state *state, int x, int y, int color)
{
	char	*dst;

	dst = state->frame.addr + (y * state->frame.line_size
			+ x * (state->frame.pixel_size));
	*(unsigned int *)dst = color;
}

void	flush_frame(t_state *state)
{
	mlx_put_image_to_window(state->mlx, state->win, state->frame.img, 0, 0);
}

void reset_frame(t_state *state) {
	#include <string.h>
	memset(state->frame.addr, 0, state->frame.line_size * HEIGHT); // TODO: to remove
}

int	render(t_state *state)
{
	reset_frame(state);
	draw_frame(state);
	flush_frame(state);
	return (0);
}
