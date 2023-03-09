/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:55:25 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/09 11:34:58 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy(t_state *state)
{
	mlx_destroy_image(state->__mlx, state->__frame.img_attr.img);
	mlx_destroy_window(state->__mlx, state->__win);
	exit(0);
}

int	key_press(int keycode, t_state *state)
{
	if (keycode == KEY_LEFT)
		state->__pa -= 0.1;
	else if (keycode == KEY_RIGHT)
		state->__pa += 0.1;
	else if (keycode == KEY_UP || keycode == KEY_W)
		set_player_pos(state, state->__px + cos(state->__pa) * 5,
			state->__py + sin(state->__pa) * 5);
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		set_player_pos(state, state->__px - cos(state->__pa) * 5,
			state->__py - sin(state->__pa) * 5);
	else if (keycode == KEY_A)
		set_player_pos(state, state->__px + cos(state->__pa - M_PI / 2) * 5,
			state->__py + sin(state->__pa - M_PI / 2) * 5);
	else if (keycode == KEY_D)
		set_player_pos(state, state->__px + cos(state->__pa + M_PI / 2) * 5,
			state->__py + sin(state->__pa + M_PI / 2) * 5);
	else if (keycode == KEY_ESC)
		destroy(state);
	trigger_render(state);
	return (0);
}

int	mouse_event(int mousecode, int x, int y, t_state *state)
{
	if (mousecode == MOUSE_LEFT)
		set_player_pos(state, x, y);
	else if (mousecode == MOUSE_SCROLL_UP)
		state->__pa += 0.1;
	else if (mousecode == MOUSE_SCROLL_DOWN)
		state->__pa -= 0.1;
	trigger_render(state);
	return (0);
}

void	init_events(t_state *state)
{
	mlx_key_hook(state->__win, key_press, state);
	mlx_do_key_autorepeaton(state->__mlx);
	mlx_mouse_hook(state->__win, mouse_event, state);
	mlx_hook(state->__win, ON_DESTROY, 0, destroy, state);
}
