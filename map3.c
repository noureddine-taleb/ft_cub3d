/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:51:59 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/10 12:52:19 by ntaleb           ###   ########.fr       */
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
