/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:55:25 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/13 14:01:20 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy(t_state *state)
{
	mlx_destroy_image(state->__mlx, state->__frame.img_attr.img);
	mlx_destroy_window(state->__mlx, state->__win);
	exit(0);
}

void	adjust_view(t_state *state, int dx, int dy)
{
	set_player_pos(state, &dx, &dy);
	move_map(state, dx, dy);
}

int	key_press(int keycode, t_state *state)
{
	if (keycode == KEY_LEFT)
		state->__pa -= 0.1;
	else if (keycode == KEY_RIGHT)
		state->__pa += 0.1;
	else if (keycode == KEY_UP || keycode == KEY_W)
		adjust_view(state, cos(state->__pa) * 5,
			sin(state->__pa) * 5);
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		adjust_view(state, -cos(state->__pa) * 5,
			-sin(state->__pa) * 5);
	else if (keycode == KEY_A)
		adjust_view(state, cos(state->__pa - M_PI / 2) * 5,
			sin(state->__pa - M_PI / 2) * 5);
	else if (keycode == KEY_D)
		adjust_view(state, cos(state->__pa + M_PI / 2) * 5,
			sin(state->__pa + M_PI / 2) * 5);
	else if (keycode == KEY_ESC)
		destroy(state);
	return (0);
}

int	mouse_event(int mousecode, int x, int y, t_state *state)
{
	(void)x;
	(void)y;
	if (mousecode == MOUSE_SCROLL_UP)
		state->__pa += 0.1;
	else if (mousecode == MOUSE_SCROLL_DOWN)
		state->__pa -= 0.1;
	return (0);
}

void	init_events(t_state *state)
{
	mlx_hook(state->__win, ON_KEYDOWN, 2L >> 1, key_press, state);
	mlx_do_key_autorepeaton(state->__mlx);
	mlx_mouse_hook(state->__win, mouse_event, state);
	mlx_hook(state->__win, ON_DESTROY, 0, destroy, state);
}
