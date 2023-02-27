/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:08:36 by abihe             #+#    #+#             */
/*   Updated: 2023/02/27 13:46:12 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>

# define MAP ((*(int (*)[state.map_height][state.map_length])state.map))

#define mapS 64
#define mapX(x) (x * 64)
#define mapY(y) (y * 64)

# define WIDTH (1920)
# define HEIGHT (1080)

enum wall_orientation {
	w_in = -1,
	w_out = 0,
	w_horizontal = 1,
	w_vertical = 2,
};

typedef struct	s_map
{
	int		map_fd;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		f;
	int		c;
	char	*line;
	int		nb_line;
	char	**l_map;
	char	player;
	int		player_x;
	int		player_y;
}	t_map;

typedef struct s_frame {
	void	*img;
	char	*addr;
	int		pixel_size;
	int		line_size;
	int		endian;
}				t_frame;

typedef struct s_state {
	void 		*mlx;
	void		*win;
	t_frame 	frame;
	
	// map
	int *map;
	int map_height;
	int map_length;
	
	// player
	int px;
	int py;
	double pa; // angle of the player
	double fov;
	double ray_offset;
} t_state;

// format: 0xTTRRGGBB
#define COLOR(t, r, g, b) (((int)t << 24) | ((int)r << 16) | ((int)g << 8) | ((int)b))
#define RED    COLOR(0x00, 0xff, 0x00, 0x00)
#define BLACK  COLOR(0x00, 0x00, 0x00, 0x00)
#define WHITE  COLOR(0x00, 0xff, 0xff, 0xff)
#define YELLOW COLOR(0x00, 0xff, 0xff, 0x00)
#define GREEN COLOR(0x00, 0x00, 0xff, 0x00)
#define GREEN_DARK  COLOR(0x00, 0x00, 0x9f, 0x33)
#define IS_WALL(val) (val == WHITE)

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
};

enum {
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_RIGHT = 124,
	KEY_LEFT = 123,
	KEY_ESC = 53,
	KEY_PLUS = 69,
	KEY_MINUS = 78,
};

enum {
	MOUSE_LEFT = 1,
	MOUSE_RIGHT = 2,
	MOUSE_MIDDLE = 3,
	MOUSE_SCROLL_UP = 4,
	MOUSE_SCROLL_DOWN = 5,
};

extern t_state state;

void init_window();
int	render(t_state *state);
void draw_frame(t_state *state);
void buffered_pixel_put(t_state *state, int x, int y, int color);
void draw_map(t_state *state);
void draw_player(t_state *state);
int is_wall(int x, int y);
int set_player_pos(int x, int y);

#endif
