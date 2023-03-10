/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:34:01 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/10 14:11:13 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reset_frame(t_state *state)
{
	t_img	*frame_img;

	frame_img = &state->__frame.img_attr;
	ft_memset(state->__frame.img_attr.addr, 0,
		frame_img->width * frame_img->height * 4);
}

void	draw_frame(t_state *state)
{
	raycasting(state);
	draw_sprite(state);
	draw_map(state);
}

void	flush_frame(t_state *state)
{
	mlx_put_image_to_window(state->__mlx, state->__win,
		state->__frame.img_attr.img, 0, 0);
}

/**
 * mac speed: 21 fps
*/
int	trigger_render(t_state *state)
{
	reset_frame(state);
	draw_frame(state);
	flush_frame(state);
	return (0);
}
