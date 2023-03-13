/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:51:59 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/13 21:51:24 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	withing_displayed_map(t_state *state, int x, int y)
{
	x -= state->displayed_map.off_x;
	y -= state->displayed_map.off_y;
	if (x < 0 || y < 0)
		return (0);
	if (x >= inflate(state->displayed_map.width)
		|| y >= inflate(state->displayed_map.height))
		return (0);
	return (1);
}

int	is_nearby_door(t_state *state, t_point p0, t_point tp)
{
	return (map_terrain(state, tp.x, tp.y) == terrain_door
		&& dist_from_origin(deflate(tp.x) - deflate(p0.x),
			deflate(tp.y) - deflate(p0.y)) <= 1);
}

void	for_each_sprite(t_state *state, void (*handler)(t_state *state, int i))
{
	int	i;

	i = 0;
	while (i < state->sprite.count)
	{
		handler(state, i);
		i++;
	}
}

void	for_each_map_pixel(t_state *state,
	void (*handler)(t_state *state, int x, int y))
{
	int	i;
	int	j;

	j = 0;
	while (j < state->map_height)
	{
		i = 0;
		while (i < state->map_width)
		{
			handler(state, i, j);
			i++;
		}
		j++;
	}
}
