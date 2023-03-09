/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:09:32 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/09 11:49:57 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	__draw_map_walls(t_state *state)
{
	int	i;
	int	j;

	i = 0;
	while (i < state->map_width)
	{
		j = 0;
		while (j < state->map_height)
		{
			draw_map_pixel(state, i, j);
			j++;
		}
		i++;
	}
}

void	__draw_map_player(t_state *state)
{
	int	i;
	int	j;

	i = state->__px;
	while (i < state->__px + PS)
	{
		j = state->__py;
		while (j < state->__py + PS)
		{
			buffered_pixel_put(state, (t_point){i, j}, yellow());
			j++;
		}
		i++;
	}
}

void	__draw_map_sprite(t_state *state)
{
	int	i;
	int	j;

	i = state->sprite.__sx;
	while (i < state->sprite.__sx + PS)
	{
		j = state->sprite.__sy;
		while (j < state->sprite.__sy + PS)
		{
			buffered_pixel_put(state, (t_point){i, j}, green());
			j++;
		}
		i++;
	}
}

void	__draw_map_rays(t_state *state)
{
	double	ra;

	ra = state->__pa - state->__fov / 2;
	while (ra < state->__pa + state->__fov / 2)
	{
		draw_ray(state, (t_point){state->__px + PS / 2, state->__py + PS / 2},
			ra, red());
		ra += state->__ray_offset;
	}
}
