/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:13:09 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/09 15:17:16 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

struct s_texture	*get_texture(t_state *state,
	const struct s_ray_intersection *intersection)
{
	if (map_terrain(state, intersection->p.x, intersection->p.y)
		== terrain_door)
		return (&state->door_texture);
	if (angle_orientation(intersection->angle, vertical) == north
		&& intersection->orientation == horizontal)
		return (&state->north_texture);
	else if (angle_orientation(intersection->angle, horizontal) == east
		&& intersection->orientation == vertical)
		return (&state->east_texture);
	else if (angle_orientation(intersection->angle, vertical) == south
		&& intersection->orientation == horizontal)
		return (&state->south_texture);
	else if (angle_orientation(intersection->angle, horizontal) == west
		&& intersection->orientation == vertical)
		return (&state->west_texture);
	die("unreachable: " __FILE__);
	return (NULL);
}

double	get_wall_offset(const struct s_ray_intersection *intersection,
		const t_img *wall_texture)
{
	if (intersection->orientation == vertical)
		return ((int)intersection->p.y % (MAPS)
			/ (double)MAPS * wall_texture->width);
	else
		return ((int)intersection->p.x % (MAPS)
			/ (double)MAPS * wall_texture->width);
}

/**
 * for higher quality wall textures
 * dx = ((double)wall_texture->width / MAPS) / state->__line_thickness
*/
void	draw_wall(t_state *state, const struct s_ray_intersection *intersection,
	double height, t_point startw)
{
	const t_img				*wall_texture
		= &get_texture(state, intersection)->img_attr;
	struct s_point			tp;
	struct s_point			wp;
	const struct s_point	tdp
		= {.x = 0,
		.y = (double)wall_texture->height / height};

	wp.x = startw.x;
	tp.x = get_wall_offset(intersection, wall_texture);
	while (wp.x < startw.x + state->__line_thickness)
	{
		tp.y = 0;
		wp.y = startw.y;
		while (wp.y < startw.y + height)
		{
			buffered_pixel_put(state, wp,
				img_pixel_read(wall_texture, tp.x, tp.y));
			wp.y++;
			tp.y += tdp.y;
		}
		wp.x++;
		tp.x += tdp.x;
	}
}

static void	draw_bg(t_state *state, double height, int startwx, int startwy)
{
	struct s_point	wp;

	wp.x = startwx;
	while (wp.x < startwx + state->__line_thickness)
	{
		wp.y = 0;
		while (wp.y < startwy)
		{
			buffered_pixel_put(state, wp, state->c);
			wp.y++;
		}
		wp.y = startwy + height;
		while (wp.y < HEIGHT)
		{
			buffered_pixel_put(state, wp, state->f);
			wp.y++;
		}
		wp.x++;
	}
}

void	draw_horizontal_line(t_state *state, int i)
{
	const struct s_ray_intersection	*intersection = &state->__zbuffer[i];
	double							height;
	int								startwx;
	int								startwy;

	if (i < 0 || i >= state->__line_count)
		return ;
	height = dist_to_wall_size(state, intersection->dist, intersection->angle);
	startwx = i * state->__line_thickness;
	startwy = (HEIGHT / 2) - height / 2;
	draw_bg(state, height, startwx, startwy);
	draw_wall(state, intersection, height, (t_point){startwx, startwy});
}
