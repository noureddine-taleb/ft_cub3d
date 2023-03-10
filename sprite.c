/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:35:00 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/10 13:35:57 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	should_display_sprite(t_state *state, double sx, double sy, double dist)
{
	if (sx < 0 || sy < 0 || sx >= WIDTH || sy >= HEIGHT)
		return (0);
	if (state->__zbuffer[(int)(sx / state->__line_thickness)].dist < dist)
		return (0);
	if (dist <= 0)
		return (0);
	return (1);
}

void	flip_sprite_state(t_state *state)
{
	state->sprite.__x_off += state->sprite.__unit_width;
	if (state->sprite.__x_off >= state->sprite.img_attr.width)
	{
		state->sprite.__x_off = 0;
		state->sprite.__y_off += state->sprite.__unit_height;
		if (state->sprite.__y_off >= state->sprite.img_attr.height)
			state->sprite.__y_off = 0;
	}
}

void	__draw_sprite(t_state *state, const double sx,
	const double sy, const double dist)
{
	const struct s_sprite	*sprite = &state->sprite;
	const double			height = 30 * sprite->__unit_height / dist;
	const double			width = 30 * sprite->__unit_width / dist;
	struct s_point			wp;
	struct s_point			sp;

	sprite = &state->sprite;
	sp.x = sprite->__x_off;
	wp.x = sx - width / 2;
	while (wp.x < (sx - width / 2) + width)
	{
		sp.y = sprite->__y_off;
		wp.y = sy - height / 2;
		while (wp.y < (sy - height / 2) + height)
		{
			buffered_pixel_put(state, wp,
				img_pixel_read(&sprite->img_attr, sp.x, sp.y));
			wp.y++;
			sp.y += sprite->__unit_height / height;
		}
		wp.x++;
		sp.x += sprite->__unit_width / width;
	}
	flip_sprite_state(state);
}

void	draw_sprite(t_state *state)
{
	const struct s_sprite	*sprite = &state->sprite;
	struct s_point			sp;
	double					dist;
	double					pixels_per_fov;

	sp.x = sprite->__sx - state->__px;
	sp.y = sprite->__sy - state->__py;
	rotate(&sp.x, &sp.y, -state->__pa);
	dist = dist_from_origin(sp.x, sp.y);
	pixels_per_fov = WIDTH / (state->__fov * dist);
	if (sp.x < 0)
		return ;
	sp.x = sp.y * pixels_per_fov + (WIDTH / 2);
	sp.y = sprite->__sz * pixels_per_fov + (HEIGHT / 2);
	if (should_display_sprite(state, sp.x, sp.y, dist))
		__draw_sprite(state, sp.x, sp.y, dist);
}
