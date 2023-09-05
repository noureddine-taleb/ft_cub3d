/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abihe <abihe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:08:36 by abihe             #+#    #+#             */
/*   Updated: 2023/03/14 10:29:10 by abihe            ###   ########.fr       */
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

# define MAPS 32
# define PS 8

# define WIDTH (1200)
# define HEIGHT (700)

enum e_terrain {
	terrain_negative_space = -1,
	terrain_wall = 0,
	terrain_positive_space = 1,
	terrain_door = 2,
};

enum e_direction {
	nodir = -1,
	east = 0,
	north = 1,
	west = 2,
	south = 3,
};

enum e_orientation {
	vertical,
	horizontal,
};

typedef struct s_int_point {
	int	x;
	int	y;
}	t_int_point;

typedef struct s_point {
	double	x;
	double	y;
}	t_point;

struct s_ray_intersection {
	t_point					p;
	enum e_orientation		orientation;
	double					dist;
	double					angle;
};

typedef struct s_img {
	void	*img;
	char	*addr;
	int		width;
	int		height;
}	t_img;

typedef struct s_frame {
	t_img	img_attr;
}	t_frame;

struct s_texture {
	char	*path;
	t_img	img_attr;
};

struct s_sprite {
	char		*path;
	t_img		img_attr;
	int			nb_sp;
	int			cols;
	int			rows;
	int			__x_off;
	int			__y_off;
	int			__unit_width;
	int			__unit_height;
	int			__sz;
	int			count;
	t_int_point	*sprites;
};

typedef struct s_map {
	int		width;
	int		height;

	int		off_x;
	int		off_y;
}	t_map;

typedef struct s_state {
	int							map_height;
	int							map_width;
	char						**map;
	t_map						displayed_map;

	void						*__mlx;
	void						*__win;
	t_frame						__frame;

	enum e_direction			initial_orientation;
	int							px;
	int							py;
	int							__px;
	int							__py;
	double						__pa;
	double						__fov;
	double						__ray_offset;
	double						__line_count;
	double						__line_thickness;

	struct s_texture			north_texture;
	struct s_texture			south_texture;
	struct s_texture			east_texture;
	struct s_texture			west_texture;
	struct s_texture			door_texture;
	struct s_sprite				sprite;
	int							f;
	int							c;

	struct s_ray_intersection	*__zbuffer;

	int							elem;
	int							flag;
}	t_state;

typedef struct s_win_fragment {
	struct s_point		startwp;
	struct s_point		starttp;
	struct s_point		w_width_height;
	struct s_point		tdp;
	const t_img			*img;
}	t_win_fragment;

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

// parser

//gnl
char				*get_next_line(int fd);
char				*ft_get_line(int fd, char *str);
int					ft_strchr(char *str, int c);
char				*ft_strjoin(char *str1, char *str2);
int					ft_strlen(char *str);
char				*ft_strdup(char *s1);
char				**ft_split(const char *s, char c);
char				*ft_strrchr(const char *str, int ch);
char				*skip_sp(char *line);
char				*set_texture(char *line);
char				*skip_sp(char *line);
int					ft_atoi(const char *str);
int					is_map_char(char c);
int					is_play(char pl);
int					if_all_empty(t_state *map);
int					if_textures_filled(t_state *map);
int					if_colors_filled(t_state *map);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					set_colors(char *line);
int					size_l(char *line, int j);
int					is_map(char *line);
void				ft_error(char *msg);
void				check_filename(char *name);
void				ft_init(t_state *map);
void				set_map(char *file, t_state *map);
void				p_pos(t_state *map, int i, int j);
void				fill_colors(char *line, t_state *map);
int					fill_textures(char *line, t_state *map);
void				all_ele_fil(t_state *map, char *line);
void				init_map(char *line, t_state *map);
void				inside_map(t_state *map);
void				map_elem(char *line, t_state *map);
void				free_double(char **str);
void				select_line(t_state *map);
void				map_char(int i, int j, t_state *map);
int					fill_do_sp(char *line, t_state *map);
int					fill_text2(char *line, t_state *map);
void				if_sprite(int i, int j, t_state *map);
void				fill_colors_norm(char *line, t_state *map);

void				init_window(t_state *state);
int					trigger_render(t_state *state);
void				draw_frame(t_state *state);
void				buffered_pixel_put(t_state *state,
						t_point p, unsigned int color);
void				draw_map(t_state *state);
void				raycasting(t_state *state);
void				set_player_pos(t_state *state, int *dx, int *dy);
void				read_img_from_xpm(t_state *state, char *xpm, t_img *img);
int					img_pixel_read(const t_img *t, int x, int y);
enum e_terrain		map_terrain(t_state *state, int x, int y);
double				dist_from_origin(double x, double y);
void				rotate(double *x, double *y, double angle);
void				draw_sprite(t_state *state, int sprite_i);
void				flip_sprite_state(t_state *state);
void				die(char *msg);
void				start(t_state *state);
void				init_events(t_state *state);
void				__draw_map_walls(t_state *state);
void				__draw_map_player(t_state *state);
void				for_each_sprite(t_state *state,
						void (*handler)(t_state *state, int i));
void				for_each_map_pixel(t_state *state,
						void (*handler)(t_state *state, int x, int y));
void				count_sprites(t_state *state, int x, int y);
void				fill_sprite(t_state *state, int x, int y);
void				__fill_sprites(t_state *state);

void				__draw_map_sprite(t_state *state, int i);
void				__draw_map_rays(t_state *state);
enum e_direction	angle_orientation(double angle, enum e_orientation o);
void				draw_horizontal_line(t_state *state, int i);
double				dist_to_wall_size(t_state *state, double dist, double ra);
void				*ft_memset(void *dest, int v, size_t len);
void				init_frame(t_state *state, t_frame *f);

int					__is_empty(t_state *state, int x, int y);
int					__is_space(t_state *state, int x, int y);
int					__is_wall(t_state *state, int x, int y);
int					__is_door(t_state *state, int x, int y);
char				__map(t_state *state, int x, int y);
int					inflate(int x);
int					deflate(int x);
int					color(int t, int r, int g, int b);
int					green(void);
int					red(void);
int					black(void);
int					white(void);
int					yellow(void);
int					error_color(void);
int					is_error_color(int c);
void				draw_map_pixel(t_state *state, int x, int y);
void				draw_ray(t_state *state, t_point p,
						double angle, int color);
void				align_point_to_next_boundary(t_int_point *dp,
						t_int_point p0, double angle, enum e_orientation o);
int					nearby_door(t_state *state, int x, int y);
void				move_map(t_state *state, int dx, int dy);
void				adjust_view(t_state *state, int dx, int dy);
int					withing_displayed_map(t_state *state, int x, int y);
int					is_nearby_door(t_state *state, t_point p0, t_point tp);
void				put_img_fragment(t_state *state, const t_win_fragment frag);

#endif
