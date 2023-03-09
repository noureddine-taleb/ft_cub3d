/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:34:48 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/09 15:25:58 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

enum e_direction	angle_orientation(double angle, enum e_orientation o)
{
	if (o == vertical)
	{
		if (sin(angle) < 0)
			return (north);
		else if (sin(angle) > 0)
			return (south);
	}
	else if (o == horizontal)
	{
		if (cos(angle) > 0)
			return (east);
		else if (cos(angle) < 0)
			return (west);
	}
	return (-1);
}

double	dist_from_origin(double x, double y)
{
	return (sqrt(x * x + y * y));
}

void	rotate(double *x, double *y, double angle)
{
	double	_sin;
	double	_cos;
	double	a;
	double	b;

	_sin = sin(angle);
	_cos = cos(angle);
	a = *x * _cos - *y * _sin;
	b = *x * _sin + *y * _cos;
	*x = a;
	*y = b;
}

void	align_point_to_next_boundary(t_int_point *dp,
	t_int_point p0, double angle, enum e_orientation o)
{
	const double		m = tan(angle);
	const t_int_point	p = {.x = dp->x + p0.x, .y = dp->y + p0.y};

	if (o == vertical)
	{
		if (angle_orientation(angle, vertical) == north)
			dp->y += -((int)p.y % MAPS) - 1;
		else if (angle_orientation(angle, vertical) == south)
			dp->y += MAPS - ((int)p.y % MAPS);
		dp->x = dp->y / m;
	}
	else if (o == horizontal)
	{
		if (angle_orientation(angle, horizontal) == west)
			dp->x += -((int)p.x % MAPS) - 1;
		else if (angle_orientation(angle, horizontal) == east)
			dp->x += MAPS - ((int)p.x % MAPS);
		dp->y = m * dp->x;
	}
}

int	nearby_door(t_state *state, int x, int y)
{
	return (map_terrain(state, x, y) == terrain_door
		&& dist_from_origin(x - state->__px, y - state->__py) <= MAPS);
}
