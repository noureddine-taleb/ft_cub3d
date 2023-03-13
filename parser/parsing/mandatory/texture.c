/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abihe <abihe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:17:25 by abihe             #+#    #+#             */
/*   Updated: 2023/03/13 19:35:42 by abihe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

int	fill_text2(char *line, t_state *map)
{
	if (ft_strncmp("WE ", line, 3) == 0)
	{
		if (map->west_texture.path)
			ft_error("duplicate element");
		map->west_texture.path = set_texture(line);
		map->elem++;
		return (1);
	}
	if (ft_strncmp("EA ", line, 3) == 0)
	{
		if (map->east_texture.path)
			ft_error("duplicate element");
		map->east_texture.path = set_texture(line);
		map->elem++;
		return (1);
	}
	return (0);
}
