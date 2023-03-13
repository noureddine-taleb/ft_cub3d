/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:20:00 by abihe             #+#    #+#             */
/*   Updated: 2023/03/13 21:37:27 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

int	is_door(t_state *map)
{
	if (map->door_texture.path)
		return (1);
	return (0);
}

void	if_sprite(int i, int j, t_state *map)
{
	(void)i;
	(void)j;
	map->sprite.rows = 4;
	map->sprite.cols = 5;
}

int	fill_do_sp(char *line, t_state *map)
{
	if (ft_strncmp("DOOR ", line, 5) == 0)
	{
		map->door_texture.path = set_texture(line);
		printf("bab found [%s]\n", map->door_texture.path);
		map->elem++;
		return (1);
	}
	if (ft_strncmp("SPRITE ", line, 7) == 0)
	{
		map->sprite.path = set_texture(line);
		printf("bomb found [%s]\n", map->sprite.path);
		map->elem++;
		return (1);
	}
	return (0);
}

void	map_char(int i, int j, t_state *map)
{
	if ((map->map[i][j] == '0' || is_play(map->map[i][j])
	|| map->map[i][j] == '2' || map->map[i][j] == '3')
		&& (i == 0 || j == 0 || map->map[i][j + 1] == '\0'
		|| map->map[i + 1] == NULL
		|| map->map[i][j + 1] == ' ' || map->map[i][j - 1] == ' '
	|| size_l(map->map[i - 1], j) || size_l(map->map[i + 1], j)
	|| map->map[i + 1][j] == ' ' || map->map[i - 1][j] == ' '))
		ft_error("Map not set properly");
}

char	*skip_sp(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (line + i);
		i++;
	}
	return (line);
}
