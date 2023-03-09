/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:58:18 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/09 11:46:05 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	die(char *msg)
{
	perror(msg);
	exit(1);
}

void	*ft_memset(void *dest, int v, size_t len)
{
	void	*p;

	p = dest;
	while (len--)
	{
		*(char *)dest++ = v;
	}
	return (p);
}

char	__map(t_state *state, int x, int y)
{
	return (state->map[y][x]);
}

int	inflate(int x)
{
	return (x * MAPS);
}

int	deflate(int x)
{
	return (x / MAPS);
}
