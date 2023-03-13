/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:09:32 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/13 21:37:07 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	__draw_map_walls(t_state *state)
{
	int			i;
	int			j;
	const int	startx = state->displayed_map.off_x;
	const int	starty = state->displayed_map.off_y;

	i = startx;
	while (i < inflate(state->map_width)
		&& i < startx + inflate(state->displayed_map.width))
	{
		j = starty;
		while (j < inflate(state->map_height)
			&& j < starty + inflate(state->displayed_map.height))
		{
			draw_map_pixel(state, i, j);
			j++;
		}
		i++;
	}
}

void	__draw_map_player(t_state *state)
{
	int			i;
	int			j;
	const int	startwx = state->__px - state->displayed_map.off_x;
	const int	startwy = state->__py - state->displayed_map.off_y;

	i = startwx;
	while (i < startwx + PS)
	{
		j = startwy;
		while (j < startwy + PS)
		{
			buffered_pixel_put(state, (t_point){i, j}, yellow());
			j++;
		}
		i++;
	}
}

void	__draw_map_sprite(t_state *state, int sprite_i)
{
	int			i;
	int			j;
	const int	startwx = state->sprite.sprites[sprite_i].x
		- state->displayed_map.off_x;
	const int	startwy = state->sprite.sprites[sprite_i].y
		- state->displayed_map.off_y;

	if (startwx >= inflate(state->displayed_map.width)
		|| startwy >= inflate(state->displayed_map.height)
	)
		return ;
	i = startwx;
	while (i < startwx + PS)
	{
		j = startwy;
		while (j < startwy + PS)
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
