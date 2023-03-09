/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:59:10 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/09 11:43:12 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_frame(t_state *state, t_frame *f)
{
	int	scratch;

	f->img_attr.width = WIDTH;
	f->img_attr.height = HEIGHT;
	f->img_attr.img = mlx_new_image(state->__mlx, WIDTH, HEIGHT);
	f->img_attr.addr = mlx_get_data_addr(f->img_attr.img,
			&scratch, &scratch, &scratch);
}

void	read_img_from_xpm(t_state *state, char *xpm, t_img *img)
{
	int	dummy;

	img->img = mlx_xpm_file_to_image(state->__mlx, xpm,
			&img->width, &img->height);
	if (!img->img)
		die("can't open the img file");
	img->addr = mlx_get_data_addr(img->img, &dummy, &dummy, &dummy);
}

int	img_pixel_read(const t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (error_color());
	dst = img->addr + (y * img->width + x) * 4;
	return (*(unsigned int *)dst);
}

void	buffered_pixel_put(t_state *state, t_point p, unsigned int color)
{
	char	*dst;
	t_img	*frame_img;

	frame_img = &state->__frame.img_attr;
	if (is_error_color(color))
		return ;
	if (p.x < 0 || p.x >= WIDTH || p.y < 0 || p.y >= HEIGHT)
		return ;
	dst = frame_img->addr + (((int)p.y * frame_img->width + (int)p.x) * 4);
	*(unsigned int *)dst = color;
}
