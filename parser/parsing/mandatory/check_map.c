/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abihe <abihe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:08:29 by abihe             #+#    #+#             */
/*   Updated: 2023/03/09 16:38:00 by abihe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../../cub3d.h"


void	ft_init(t_state *map)
{
	map->north_texture.path = NULL;
	map->south_texture.path = NULL;
	map->west_texture.path= NULL;
	map->east_texture.path= NULL;
	map->map = NULL;
	map->initial_orientation = 0;
	map->px = 0;
	map->py = 0;
	map->f = -1;
	map->c = -1;
	map->elem = 0;
	map->flag = -1;
	map->map_height = 0;
	map->map_width = 0;
}

void	check_textures(t_state *map, char *line, int fd)
{
	while (line)
	{
		all_ele_fil(map, line);
		free(line);
		line = get_next_line(fd);
	}
}

void	colors_check(char *line)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (line[i])
	{
		if (line[i] == ',' && line[i + 1] == ',')
			ft_error("To much commas");
		else if (line[i] == ',')
			c++;
		i++;
	}
	if (c != 2 || line[i - 1] == ',')
		ft_error("Color does not set correctly!");
}

int	set_colors(char *line)
{
	char	**rgb;
	char	**color;
	int		r;
	int		g;
	int		b;

	colors_check(line);
	color = ft_split(line, ' ');
	if (color[2] || !color[1])
		ft_error("Color elements not set very well");
	rgb = ft_split(color[1], ',');
	if (!rgb || !rgb[1] || !rgb[2])
		ft_error("Color does not set correctly!");
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		ft_error("Color value are wrong!");
	free_double(rgb);
	free_double(color);
	return (r << 16 | g << 8 | b);
}

void	set_map(char *file, t_state *map)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("File not found!");
	line = get_next_line(fd);
	if (!line)
		ft_error("Empty file!");
	while (line)
	{
		map_elem(line, map);
		free(line);
		line = get_next_line(fd);
	}
	map->map = malloc(sizeof(char *) * (map->map_height + 1));
	map->map[0] = NULL;
	close(fd);
	fd = open(file, O_RDONLY);
		line = get_next_line(fd);
	check_textures(map, line, fd);
	if (map->map_height == 0)
		ft_error("map not set yet!");
}
