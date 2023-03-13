/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:34:42 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/13 14:07:31 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_attributes(t_state *state)
{
	state->__fov = M_PI / 2;
	state->__ray_offset = 0.001;
	state->__pa = -(M_PI / 2) * state->initial_orientation;
	state->__line_count = state->__fov / state->__ray_offset;
	state->__line_thickness = WIDTH / state->__line_count;
	state->__zbuffer = malloc((state->__line_count + 1)
			* sizeof(*state->__zbuffer));
	state->displayed_map.height = 8;
	state->displayed_map.width = 8;
	state->__px = 0;
	state->__py = 0;
	state->displayed_map.off_x = 0;
	state->displayed_map.off_y = 0;
	state->__px = state->px * MAPS + MAPS / 2;
	state->__py = state->py * MAPS + MAPS / 2;
	move_map(state, state->__px - inflate(state->displayed_map.width / 2),
		state->__py - inflate(state->displayed_map.height / 2));
}

void	init_sprite(t_state *state)
{
	if (state->sprite.path)
		read_img_from_xpm(state, state->sprite.path, &state->sprite.img_attr);
	else
		return ;
	state->sprite.__sx = state->sprite.sx * MAPS + MAPS / 2;
	state->sprite.__sy = state->sprite.sy * MAPS + MAPS / 2;
	state->sprite.__sz = 8;
	state->sprite.__x_off = 0;
	state->sprite.__y_off = 0;
	state->sprite.__unit_width = state->sprite.img_attr.width
		/ state->sprite.cols;
	state->sprite.__unit_height = state->sprite.img_attr.height
		/ state->sprite.rows;
}

void	init_textures(t_state *state)
{
	read_img_from_xpm(state, state->north_texture.path,
		&state->north_texture.img_attr);
	read_img_from_xpm(state, state->south_texture.path,
		&state->south_texture.img_attr);
	read_img_from_xpm(state, state->west_texture.path,
		&state->west_texture.img_attr);
	read_img_from_xpm(state, state->east_texture.path,
		&state->east_texture.img_attr);
	if (state->door_texture.path)
		read_img_from_xpm(state, state->door_texture.path,
			&state->door_texture.img_attr);
}

void	start(t_state *state)
{
	parser_stub(state);
	init_attributes(state);
	init_window(state);
	init_textures(state);
	init_sprite(state);
	mlx_loop_hook(state->__mlx, trigger_render, state);
	mlx_loop(state->__mlx);
}
