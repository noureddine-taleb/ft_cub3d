/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abihe <abihe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:15:28 by abihe             #+#    #+#             */
/*   Updated: 2023/03/06 19:05:59 by abihe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*join;
	int		i;
	int		j;

	if (!str1 || !str2)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2)) + 1);
	if (!join)
		return (NULL);
	i = 0;
	while (str1[i])
	{
		join[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
		join[i++] = str2[j++];
	join[i] = '\0';
	free(str1);
	return (join);
}
