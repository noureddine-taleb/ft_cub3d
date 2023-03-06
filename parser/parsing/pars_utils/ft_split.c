/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abihe <abihe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 10:33:34 by abihe             #+#    #+#             */
/*   Updated: 2023/03/06 19:05:59 by abihe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

static size_t	count_words(const char *s, char c)
{
	size_t	words;
	int		state;
	int		i;

	words = 0;
	state = 1;
	i = 0;
	while (s[i] != 0 && s[i] != '\0')
	{
		if (s[i] == c)
			state = 1;
		else if (state == 1)
		{
			words++;
			state = 0;
		}
		i++;
	}
	return (words);
}

static size_t	sizeof_word(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && (s[i] != c))
		i++;
	return (i);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	size_t	index;
	size_t	i;

	if (s == 0)
		return (0);
	tab = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (tab == 0)
		return (0);
	index = 0;
	while (count_words(s, c))
	{
		while (*s == c)
			s++;
		tab[index] = malloc(sizeof(char) * (sizeof_word(s, c) + 1));
		if (tab[index] == 0)
			return (0);
		i = 0;
		while (*s && (*s != c))
			tab[index][i++] = *s++;
		tab[index][i] = 0;
		index++;
	}
	tab[index] = 0;
	return (tab);
}
