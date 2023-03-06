/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abihe <abihe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:27:37 by abihe             #+#    #+#             */
/*   Updated: 2023/03/06 19:05:59 by abihe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

static int	handle_overflow(int sign, unsigned long long nb)
{
	while (nb > 9223372036854775807)
	{
		if (sign == -1)
			return (0);
		if (sign == 1)
			return (-1);
		nb++;
	}
	return ((int)nb * sign);
}

int	ft_atoi(const char *str)
{
	int						i;
	int						sign;
	unsigned long long		nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	nb = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			nb = nb * 10 + (str[i++] - '0');
		else
			ft_error("Find deferent color value");
	}
	return (handle_overflow(sign, nb));
}
