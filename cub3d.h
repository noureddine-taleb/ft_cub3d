/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abihe <abihe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:08:36 by abihe             #+#    #+#             */
/*   Updated: 2023/03/06 19:16:56 by abihe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>

# define MAP(x, y) (state.map[y][x])

#define mapS 32
#define mapX(x) (x * mapS)
#define mapY(y) (y * mapS)
#define pS 8

// # define WIDTH (1570)
// # define HEIGHT (1080)
# define WIDTH (1570+1300)
# define HEIGHT (1080+340)

// format: 0xTTRRGGBB
#define COLOR(t, r, g, b) (((int)t << 24) | ((int)r << 16) | ((int)g << 8) | ((int)b))
#define RED    COLOR(0x00, 0xff, 0x00, 0x00)
#define BLACK  COLOR(0x00, 0x00, 0x00, 0x00)
#define WHITE  COLOR(0x00, 0xff, 0xff, 0xff)
#define YELLOW COLOR(0x00, 0xff, 0xff, 0x00)
#define GREEN COLOR(0x00, 0x00, 0xff, 0x00)
#define GREEN_DARK  COLOR(0x00, 0x00, 0x9f, 0x33)
// these macros use the minified x and y
#define __IS_EMPTY(x, y) (x >= state.map_width || y >= state.map_height || x < 0 || y < 0)
#define __IS_WALL(x, y) (MAP(x, y) == '1')
#define __IS_SPACE(x, y) (MAP(x, y) == '0')

enum terrain {
	terrain_negative_space = -1,
	terrain_wall = 0,
	terrain_positive_space = 1,
};

enum orientation {
	east = 0,
	north = 1,
	west = 2,
	south = 3,
};

enum wall_orientation {
	vertical,
	horizontal,
};

struct ray_intersection {
	int x, y;
	enum wall_orientation orientation;
	double dist;
	double angle;
};

typedef struct s_img {
	void	*img;
	char	*addr;
	int width;
	int height;
} t_img;

typedef struct s_frame {
	t_img img_attr;
} t_frame;

struct texture {
	char *path;
	t_img img_attr;
};

struct sprite {
	char *path;
	t_img img_attr;
	int sx;
	int sy;
	int __sx;
	int __sy;
	int __sz;
};

typedef struct s_state {
	// map
	int map_height;
	int map_width;
	char	**map;

	// minilibc
	void 		*__mlx;
	void		*__win;
	t_frame 	__frame;

	// player
	enum orientation initial_orientation;
	int px;
	int py;
	int __px;
	int __py;
	double __pa; // angle of the player
	double __fov;
	double __ray_offset;
	double __line_count;
	double __line_thickness;

	// texture
	struct texture north_texture;
	struct texture south_texture;
	struct texture east_texture;
	struct texture west_texture;
	struct sprite  sprite;
	int		f;		// floor color
	int		c;		// ceiling color

	struct ray_intersection *__zbuffer;

	int		elem;
	int		flag;
} t_state;

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
	KEY_W = 13,
	KEY_S = 1,
	KEY_A = 0,
	KEY_D = 2,
};

enum {
	MOUSE_LEFT = 1,
	MOUSE_RIGHT = 2,
	MOUSE_MIDDLE = 3,
	MOUSE_SCROLL_UP = 4,
	MOUSE_SCROLL_DOWN = 5,
};

extern t_state state;

// parser

//gnl
char	*get_next_line(int fd);
char	*ft_get_line(int fd, char *str);
int		ft_strchr(char *str, int c);
char	*ft_strjoin(char *str1, char *str2);
int		ft_strlen(char *str);
char	*ft_strdup(char *s1);
//pars
char	**ft_split(const char *s, char c);
char	*ft_strrchr(const char *str, int ch);
char	*skip_sp(char *line);
char	*set_texture(char *line);
char	*skip_sp(char *line);
int		ft_atoi(const char *str);
int		is_map_char(char c);
int		is_play(char pl);
int		if_all_empty(t_state *map);
int		if_textures_filled(t_state *map);
int		if_colors_filled(t_state *map);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		set_colors(char *line);
int		size_l(char *line, int j);
int		is_map(char *line);
void	ft_error(char *msg);
void	check_filename(char *name);
void	ft_init(t_state *map);
void	set_map(char *file, t_state *map);
void	p_pos(t_state *map, int i, int j);
void	fill_colors(char *line, t_state *map);
int		fill_textures(char *line, t_state *map);
void	all_ele_fil(t_state *map, char *line);
void	init_map(char *line, t_state *map);
void	inside_map(t_state *map);
void	map_elem(char *line, t_state *map);
void	free_double(char **str);

// execution
void init_window();
int	render();
void draw_frame();
void buffered_pixel_put(int x, int y, unsigned int color);
void draw_map();
void raycasting();
void set_player_pos(int x, int y);
void read_img_from_xpm(char *xpm, t_img *img);
int	img_pixel_read(t_img *t, int x, int y);
enum terrain map_terrain(int x, int y);
double dist_from_origin(int x, int y);
void rotate(double *x, double *y, double angle);
void raycasting();
void draw_sprite();
void die(char *msg);
void draw();

#endif
