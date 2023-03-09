MINILIBX_DIR := minilibx
MINILIBX := $(MINILIBX_DIR)/libmlx.a
TARGET := cub3D
SRCS := start.c cub3d.c window.c raycaster.c draw.c map.c map2.c map3.c player.c sprite.c math.c event.c helpers.c helpers2.c helpers3.c image.c debug.c \
			parser/parsing/mandatory/check_map.c \
			parser/parsing/gnl/get_next_line.c \
			parser/parsing/gnl/get_next_line_utils.c \
			parser/main.c \
			parser/parsing/mandatory/check_filename.c \
			parser/parsing/mandatory/check_elem.c \
			parser/parsing/mandatory/set_elem.c \
			parser/parsing/mandatory/util_elem.c \
			parser/parsing/mandatory/set_map.c \
			parser/parsing/pars_utils/ft_split.c \
			parser/parsing/pars_utils/ft_strdup.c \
			parser/parsing/pars_utils/ft_atoi.c
HDRS := cub3d.h
# TODO: remove debugging instruments
CFLAGS := -DBUFFER_SIZE=255 -O2 -I $(MINILIBX_DIR) -lm -framework OpenGL -framework AppKit -g -fsanitize=address -fno-omit-frame-pointer # -Wall -Wextra -Werror

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS) $(MINILIBX)
	$(CC) $(CFLAGS) $(SRCS) $(MINILIBX) -o $@

$(MINILIBX): $(MINILIBX_DIR)
	$(MAKE) -C $^

clean:
	-rm -f *.o

fclean: clean
	-rm $(TARGET)

re: fclean all
