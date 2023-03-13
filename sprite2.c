/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:00:25 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/13 22:00:40 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_sprites(t_state *state, int x, int y)
{
	if (__map(state, x, y) == '3')
		state->sprite.count++;
}

void	fill_sprite(t_state *state, int x, int y)
{
	static int	sprite_i = 0;

	if (__map(state, x, y) == '3')
	{
		state->sprite.sprites[sprite_i].x = inflate(x) + MAPS / 2;
		state->sprite.sprites[sprite_i].y = inflate(y) + MAPS / 2;
		state->map[y][x] = '0';
		sprite_i++;
	}
}

void	__fill_sprites(t_state *state)
{
	for_each_map_pixel(state, count_sprites);
	if (!state->sprite.count)
		return ;
	state->sprite.sprites = malloc(sizeof(*state->sprite.sprites)
			* state->sprite.count);
	for_each_map_pixel(state, fill_sprite);
}
