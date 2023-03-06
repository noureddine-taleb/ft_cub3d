/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abihe <abihe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:07:12 by abihe             #+#    #+#             */
/*   Updated: 2023/03/06 19:05:59 by abihe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		d;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && i + 1 < n)
	i++;
	d = (unsigned char)s1[i] - (unsigned char)s2[i];
	if (!d || !n)
		return (0);
	else if (d < 0)
		return (-1);
	else
		return (1);
}

char	*ft_strrchr(const char *str, int ch)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i != 0)
	{
		if (str[i] == (char) ch)
			return ((char *)&str[i]);
		i--;
	}
	if (str[i] == (char) ch)
		return ((char *)&str[i]);
	return (0);
}

void	check_filename(char *name)
{
	if (ft_strchr(name, '.'))
	{
		if (ft_strncmp(ft_strrchr(name, '.'), ".cub", 4))
			ft_error("Something wrong with the map file!");
	}
	else
		ft_error("Something wrong with the map file");
}

void	ft_error(char *msg)
{
	printf("Error\n%s\n", msg);
	exit(1);
}
