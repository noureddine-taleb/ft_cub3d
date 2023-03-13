/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abihe <abihe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:14:31 by abihe             #+#    #+#             */
/*   Updated: 2023/03/13 17:37:57 by abihe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

int	is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1')
		return (1);
	return (0);
}

enum e_direction	char_to_or(char c)
{
	if (c == 'N')
		return (north);
	if (c == 'S')
		return (south);
	if (c == 'E')
		return (east);
	if (c == 'W')
		return (west);
	die("undefined orientation");
	return (-1);
}

void	p_pos(t_state *map, int i, int j)
{
	map->px = j;
	map->py = i;
	map->initial_orientation = char_to_or(map->map[i][j]);
	map->map[i][j] = '0';
}

int	size_l(char *line, int j)
{
	if (j > ft_strlen(line) - 1)
		return (1);
	return (0);
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
