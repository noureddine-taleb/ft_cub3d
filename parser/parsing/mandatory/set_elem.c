/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abihe <abihe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:38:04 by abihe             #+#    #+#             */
/*   Updated: 2023/03/14 10:23:46 by abihe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../../cub3d.h"

char	*set_texture(char *line)
{
	char	*result;
	char	**sp;

	sp = ft_split(line, ' ');
	if (!sp || !sp[1] || sp[2])
		ft_error("something wrong with texture");
	result = ft_strdup(sp[1]);
	if (open(result, O_RDONLY) == -1)
		ft_error("404! in texture file!");
	free_double(sp);
	return (result);
}

int	fill_textures(char *line, t_state *map)
{
	if (ft_strncmp("NO ", line, 3) == 0)
	{
		if (map->north_texture.path)
			ft_error("duplicate element");
		map->north_texture.path = set_texture(line);
		map->elem++;
		return (1);
	}
	if (ft_strncmp("SO ", line, 3) == 0)
	{
		if (map->south_texture.path)
			ft_error("duplicate element");
		map->south_texture.path = set_texture(line);
		map->elem++;
		return (1);
	}
	return (0);
}

void	fill_colors(char *line, t_state *map)
{
	if ((((ft_strncmp("F ", line, 2) == 0) && map->f == -1)
			|| ((ft_strncmp("C ", line, 2) == 0) && map->c == -1))
		&& map->elem < 4)
		ft_error("a texture is not set yet!");
	if (ft_strncmp("F ", line, 2) == 0)
	{
		if (map->f != -1)
			ft_error("the element has already filled 1");
		map->f = set_colors(line);
		map->elem++;
	}
	else if (ft_strncmp("C ", line, 2) == 0)
	{
		if (map->c == -1)
		{
			map->c = set_colors(line);
			map->elem++;
		}
		else
			ft_error("the element has already filled 2");
	}
	else
		fill_colors_norm(line, map);
}

void	init_map(char *line, t_state *map)
{
	static int	i;

	if (i < map->map_height)
	{
		map->map[i] = ft_strdup(line);
		i++;
	}
	if (i == map->map_height)
		map->map[i] = NULL;
}

void	all_ele_fil(t_state *map, char *line)
{
	if (line[0] == ' ' && !if_all_empty(map) && !map->map[0])
		line = skip_sp(line);
	if (!line[0])
		return ;
	if (!if_textures_filled(map))
	{
		if (fill_text2(line, map))
			return ;
		if (fill_textures(line, map))
			return ;
	}
	if (!if_colors_filled(map))
		fill_colors(line, map);
	else if (if_all_empty(map))
	{
		if (!line[0])
			return ;
		if (!is_map_char(line[0]))
			ft_error("Wrong element inside the file");
		init_map(line, map);
	}
}
