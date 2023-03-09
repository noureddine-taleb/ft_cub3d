/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:47:39 by abihe             #+#    #+#             */
/*   Updated: 2023/03/08 19:19:07 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int main(int argc, char **argv)
{
	t_state *state = malloc(sizeof(*state));
	if(argc != 2)
		ft_error("Wrong number of arguments");
	check_filename(argv[1]);
	ft_init(state);
	set_map(argv[1], state);
	if(!if_colors_filled(state) || !if_textures_filled(state))
		ft_error("Elements not filled");
	inside_map(state);
	start(state);
	return (0);
}
