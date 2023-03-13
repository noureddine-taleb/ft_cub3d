/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:59:10 by ntaleb            #+#    #+#             */
/*   Updated: 2023/03/13 18:54:34 by ntaleb           ###   ########.fr       */
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

void	put_img_fragment(t_state *state, const t_win_fragment frag)
{
	struct s_point				wp;
	struct s_point				tp;

	wp = frag.startwp;
	tp = frag.starttp;
	while (wp.x < frag.startwp.x + frag.w_width_height.x)
	{
		if (wp.x >= 0 && wp.x < state->__frame.img_attr.width)
		{
			tp.y = frag.starttp.y;
			wp.y = frag.startwp.y;
			while (wp.y < frag.startwp.y + frag.w_width_height.y)
			{
				if (wp.y >= 0 && wp.y < state->__frame.img_attr.height)
					buffered_pixel_put(state, (t_point){.x = wp.x, .y = wp.y},
						img_pixel_read(frag.img, tp.x, tp.y));
				wp.y++;
				tp.y += frag.tdp.y;
			}
		}
		wp.x++;
		tp.x += frag.tdp.x;
	}
}
