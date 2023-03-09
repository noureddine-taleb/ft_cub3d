/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:33:56 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/09 11:47:28 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map_pixel(t_state *state, int x, int y)
{
	int	i;
	int	j;

	i = inflate(x);
	while (i < inflate(x) + MAPS)
	{
		j = inflate(y);
		while (j < inflate(y) + MAPS)
		{
			if (__is_wall(state, x, y))
				buffered_pixel_put(state, (t_point){i, j}, white());
			else if (__is_door(state, x, y))
				buffered_pixel_put(state, (t_point){i, j}, yellow());
			else
				buffered_pixel_put(state, (t_point){i, j}, black());
			j++;
		}
		i++;
	}
}

void	draw_ray(t_state *state, t_point p, double angle, int color)
{
	double	dx;
	double	dy;
	double	x0;
	double	y0;

	dx = cos(angle);
	dy = sin(angle);
	x0 = p.x;
	y0 = p.y;
	while (map_terrain(state, p.x, p.y) == terrain_positive_space
		|| (map_terrain(state, p.x, p.y) == terrain_door
			&& dist_from_origin(deflate(p.x) - deflate(x0),
				deflate(p.y) - deflate(y0)) <= 1)
	)
	{
		buffered_pixel_put(state, p, color);
		p.x += dx;
		p.y += dy;
	}
}

enum e_terrain	map_terrain(t_state *state, int x, int y)
{
	x = deflate(x);
	y = deflate(y);
	if (__is_empty(state, x, y))
		return (terrain_negative_space);
	if (__is_wall(state, x, y))
		return (terrain_wall);
	if (__is_door(state, x, y))
		return (terrain_door);
	return (terrain_positive_space);
}

void	draw_map(t_state *state)
{
	__draw_map_walls(state);
	__draw_map_player(state);
	__draw_map_rays(state);
	__draw_map_sprite(state);
}
