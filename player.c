/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:34:52 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/10 12:04:11 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_pos(t_state *state, int dx, int dy)
{
	int	x;
	int	y;

	x = dx + state->__px;
	y = dy + state->__py;
	if (map_terrain(state, x, state->__py) == terrain_positive_space
		|| map_terrain(state, x, state->__py) == terrain_door)
		state->__px = x;
	if (map_terrain(state, state->__px, y) == terrain_positive_space
		|| map_terrain(state, state->__px, y) == terrain_door)
		state->__py = y;
}
