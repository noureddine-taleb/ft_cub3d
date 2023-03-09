/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:14:31 by abihe             #+#    #+#             */
/*   Updated: 2023/03/08 15:27:41 by ntaleb           ###   ########.fr       */
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

enum e_direction char_to_or(char c)
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
	return -1;
}

void	p_pos(t_state *map, int i, int j)
{
	map->px = i;
	map->py = j;
	map->initial_orientation = char_to_or(map->map[i][j]);
}

int	size_l(char *line, int j)
{
	if (j > ft_strlen(line) - 1)
		return (1);
	return (0);
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