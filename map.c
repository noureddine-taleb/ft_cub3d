/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:33:56 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/13 21:33:12 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map_pixel(t_state *state, int mx, int my)
{
	const int			wx = mx - state->displayed_map.off_x;
	const int			wy = my - state->displayed_map.off_y;

	if (__is_wall(state, deflate(mx), deflate(my)))
		buffered_pixel_put(state, (t_point){.x = wx, .y = wy}, white());
	else if (__is_door(state, deflate(mx), deflate(my)))
		buffered_pixel_put(state, (t_point){.x = wx, .y = wy}, yellow());
	else
		buffered_pixel_put(state, (t_point){.x = wx, .y = wy}, black());
}

void	draw_ray(t_state *state, t_point p, double angle, int color)
{
	double			dx;
	double			dy;
	const t_point	p0 = p;

	dx = cos(angle);
	dy = sin(angle);
	while ((map_terrain(state, p.x, p.y) == terrain_positive_space
			|| is_nearby_door(state, p0, p))
		&& withing_displayed_map(state, p.x, p.y)
	)
	{
		buffered_pixel_put(state,
			(t_point){.x = p.x - state->displayed_map.off_x,
			.y = p.y - state->displayed_map.off_y}, color
			);
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
	for_each_sprite(state, __draw_map_sprite);
	flip_sprite_state(state);
}

void	move_map(t_state *state, int dx, int dy)
{
	int	new_off_x;
	int	new_off_y;

	new_off_x = state->displayed_map.off_x + dx;
	new_off_y = state->displayed_map.off_y + dy;
	if (inflate(state->map_width)
		- new_off_x < inflate(state->displayed_map.width))
		new_off_x = inflate(state->map_width)
			- inflate(state->displayed_map.width);
	if (inflate(state->map_height)
		- new_off_y < inflate(state->displayed_map.height))
		new_off_y = inflate(state->map_height)
			- inflate(state->displayed_map.height);
	if (new_off_x < 0)
		new_off_x = 0;
	if (new_off_y < 0)
		new_off_y = 0;
	state->displayed_map.off_x = new_off_x;
	state->displayed_map.off_y = new_off_y;
}
