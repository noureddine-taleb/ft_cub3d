/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abihe <abihe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:47:39 by abihe             #+#    #+#             */
/*   Updated: 2023/03/09 16:50:11 by abihe            ###   ########.fr       */
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
	select_line(state);
	for (int i = 0; i < state->map_height; i++)
		printf("|%s|\n", state->map[i]);
	start(state);
	return (0);
}
