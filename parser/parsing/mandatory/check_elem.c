/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abihe <abihe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:07:17 by abihe             #+#    #+#             */
/*   Updated: 2023/03/13 18:06:57 by abihe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

int	if_textures_filled(t_state *map)
{
	if (map->north_texture.path && map->south_texture.path
		&& map->east_texture.path && map->west_texture.path)
		return (1);
	return (0);
}

int	if_colors_filled(t_state *map)
{
	if (map->c != -1 && map->f != -1)
		return (1);
	return (0);
}

int	if_all_empty(t_state *map)
{
	if (if_textures_filled(map) && if_colors_filled(map))
		return (1);
	return (0);
}

int	is_play(char pl)
{
	if (pl == 'N' || pl == 'S' || pl == 'E' || pl == 'W')
		return (1);
	return (0);
}

int	is_map_char(char c)
{
	if (is_play(c) || c == ' ' || c == '0' || c == '1' || c == '2' || c == '3')
		return (1);
	return (0);
}
