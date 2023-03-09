/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:23:30 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/08 18:38:36 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color(int t, int r, int g, int b)
{
	return (((int)t << 24) | ((int)r << 16) | ((int)g << 8) | ((int)b));
}

int	red(void)
{
	return (color(0x00, 0xff, 0x00, 0x00));
}

int	black(void)
{
	return (color(0x00, 0x00, 0x00, 0x00));
}

int	white(void)
{
	return (color(0x00, 0xff, 0xff, 0xff));
}

int	yellow(void)
{
	return (color(0x00, 0xff, 0xff, 0x00));
}
