/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abihe <abihe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:49:22 by abihe             #+#    #+#             */
/*   Updated: 2023/03/06 19:24:16 by abihe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

void	map_elem(char *line, t_state *map)
{
	if (is_map(line) || line[0] == '1')
	{
		if (map->flag == -1)
			map->flag = 0;
		map->map_height++;
	}
	else if (!map->flag)
		map->flag = 1;
	if ((is_map(line) || line[0] == '1') && map->flag)
	{
		if (line)
			free(line);
		ft_error("somthing wrong with the map");
	}
}

void	check_pla(int i, int j, t_state *map)
{
	if (map->initial_orientation == '\0')
		p_pos(map, i, j);
	else
		ft_error("There is more than one player!");
}

void	inside_map(t_state *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if ((map->map[i][j] == '0' || is_play(map->map[i][j]))
				&& (i == 0 || j == 0 || map->map[i][j + 1] == '\0' || map->map[i + 1] == NULL
				|| map->map[i][j + 1] == ' ' || map->map[i][j - 1] == ' '
				|| size_l(map->map[i - 1], j) || size_l(map->map[i + 1], j)
				|| map->map[i + 1][j] == ' ' || map->map[i - 1][j] == ' '))
				ft_error("Map not set properly");
			if (!is_map_char(map->map[i][j]))
				ft_error("There is a foreign charachter!");
			if (is_play(map->map[i][j]))
				check_pla(i, j, map);
			j++;
		}
		i++;
	}
	if (map->initial_orientation == '\0')
		ft_error("No player found!");
}
