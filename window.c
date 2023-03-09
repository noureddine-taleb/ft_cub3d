/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:35:05 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/08 19:19:43 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * initialise the graphics
 * bind keyboard/mouse events
 * call the render function when necessary
*/

void	init_window(t_state *state)
{
	state->__mlx = mlx_init();
	init_frame(state, &state->__frame);
	state->__win = mlx_new_window(state->__mlx, WIDTH, HEIGHT, "cub3d");
	init_events(state);
}
