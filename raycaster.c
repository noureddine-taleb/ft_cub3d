/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:34:55 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/09 15:25:50 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	dist_to_wall_size(t_state *state, double dist, double ra)
{
	dist = dist * cos(state->__pa - ra);
	dist = (HEIGHT * 20) / dist;
	return (dist);
}

struct s_ray_intersection	cast_ray_vertical(t_state *state, double angle)
{
	struct s_ray_intersection		intersection;
	const t_int_point				p0 = {.x = state->__px, .y = state->__py};
	t_int_point						dp;

	intersection = (struct s_ray_intersection){.angle = angle};
	dp = (t_int_point){0};
	intersection.orientation = horizontal;
	if (sin(angle))
	{
		while (map_terrain(state, dp.x + p0.x, dp.y + p0.y)
			== terrain_positive_space
			|| nearby_door(state, dp.x + p0.x, dp.y + p0.y)
		)
			align_point_to_next_boundary(&dp, p0,
				angle, vertical);
		intersection.dist = dist_from_origin(dp.x,
				dp.y);
		intersection.p.x = dp.x + p0.x;
		intersection.p.y = dp.y + p0.y;
	}
	else
	{
		intersection.dist = INFINITY;
	}
	return (intersection);
}

struct s_ray_intersection	cast_ray_horizontal(t_state *state, double angle)
{
	struct s_ray_intersection		intersection;
	const t_int_point				p0 = {.x = state->__px, .y = state->__py};
	t_int_point						dp;

	intersection = (struct s_ray_intersection){.angle = angle};
	dp = (t_int_point){0};
	intersection.orientation = vertical;
	if (cos(angle))
	{
		while (map_terrain(state, dp.x + p0.x, dp.y + p0.y)
			== terrain_positive_space
			|| nearby_door(state, dp.x + p0.x, dp.y + p0.y)
		)
			align_point_to_next_boundary(&dp, p0,
				angle, horizontal);
		intersection.dist = dist_from_origin(dp.x,
				dp.y);
		intersection.p.x = dp.x + p0.x;
		intersection.p.y = dp.y + p0.y;
	}
	else
	{
		intersection.dist = INFINITY;
	}
	return (intersection);
}

static void	cast_ray(t_state *state, struct s_ray_intersection *intersection)
{
	const struct s_ray_intersection	v = cast_ray_vertical(state,
			intersection->angle);
	const struct s_ray_intersection	h = cast_ray_horizontal(state,
			intersection->angle);

	if (v.dist < h.dist)
		*intersection = v;
	else
		*intersection = h;
}

void	raycasting(t_state *state)
{
	int		i;
	double	ra;

	i = 0;
	ra = state->__pa - state->__fov / 2;
	while (ra < state->__pa + state->__fov / 2)
	{
		state->__zbuffer[i].angle = ra;
		cast_ray(state, &state->__zbuffer[i]);
		draw_horizontal_line(state, i);
		ra += state->__ray_offset;
		i++;
	}
}
