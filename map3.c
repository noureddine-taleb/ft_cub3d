/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:25:45 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/08 19:28:14 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// these macros use the minified x and y
int	__is_empty(t_state *state, int x, int y)
{
	return (x >= state->map_width || y >= state->map_height
		|| x < 0 || y < 0 || __map(state, x, y) == ' ');
}

int	__is_space(t_state *state, int x, int y)
{
	return (__map(state, x, y) == '0');
}

int	__is_wall(t_state *state, int x, int y)
{
	return (__map(state, x, y) == '1');
}

int	__is_door(t_state *state, int x, int y)
{
	return (__map(state, x, y) == '2');
}
