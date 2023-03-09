/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:39:18 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/08 18:39:18 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	green(void)
{
	return (color(0x00, 0x00, 0xff, 0x00));
}

int	error_color(void)
{
	return (color(0xff, 0x00, 0x00, 0x00));
}

int	is_error_color(int c)
{
	return (c & 0xff000000);
}
