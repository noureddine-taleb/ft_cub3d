/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abihe <abihe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:49:22 by abihe             #+#    #+#             */
/*   Updated: 2023/03/13 17:31:55 by abihe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

void	map_elem(char *line, t_state *map)
{
	if (is_map(line) || line[0] == '1')
	{
		if (ft_strlen(line) > map->map_width)
			map->map_width = ft_strlen(line);
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
	if (map->initial_orientation == nodir)
		p_pos(map, i, j);
	else
		ft_error("There is more than one player!");
}

void	add_spaces(t_state *map, int i)
{
	int	j;

	j = ft_strlen(map->map[i]);
	while (j < map->map_width)
	{
		map->map[i] = ft_strjoin(map->map[i], " ");
		j++;
	}
}

void	select_line(t_state *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		if ((ft_strlen(map->map[i])) < map->map_width)
			add_spaces(map, i);
		i++;
	}
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
			map_char(i, j, map);
			if (!is_map_char(map->map[i][j]))
				ft_error("There is a foreign charachter!");
			if (is_play(map->map[i][j]))
				check_pla(i, j, map);
			if_sprite(i, j, map);
			j++;
		}
		i++;
	}
	if (map->initial_orientation == nodir)
		ft_error("No player found!");
}
