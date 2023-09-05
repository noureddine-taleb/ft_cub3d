TARGET := cub3D
SRCS := start.c cub3d.c window.c raycaster.c draw.c map.c map2.c map3.c map4.c player.c sprite.c sprite2.c math.c event.c helpers.c helpers2.c helpers3.c image.c \
			parser/parsing/mandatory/check_map.c \
			parser/parsing/gnl/get_next_line.c \
			parser/parsing/gnl/get_next_line_utils.c \
			parser/main.c \
			parser/parsing/mandatory/check_filename.c \
			parser/parsing/mandatory/check_elem.c \
			parser/parsing/mandatory/set_elem.c \
			parser/parsing/mandatory/util_elem.c \
			parser/parsing/mandatory/check2.c \
			parser/parsing/mandatory/texture.c \
			parser/parsing/mandatory/set_map.c \
			parser/parsing/pars_utils/ft_split.c \
			parser/parsing/pars_utils/ft_strdup.c \
			parser/parsing/pars_utils/ft_atoi.c
HDRS := cub3d.h
OBJS := ${SRCS:.c=.o}

LDFLAGS := -Lmlx -lmlx_Linux -lm -Wall -Wextra -lXext -lX11 -lm -lz # -Werror -framework OpenGl -framework AppKit -g -fsanitize=address -fno-omit-frame-pointer

all: $(TARGET)

%.o: %.c
	$(CC) -Wall -Wextra -DBUFFER_SIZE=255 -Imlx -c $< -o $@

$(TARGET): $(OBJS) $(HDRS)
	$(CC) $(OBJS) $(LDFLAGS) $(MINILIBX) -o $@

clean:
	-rm -f *.o

fclean: clean
	-rm $(TARGET)

re: fclean all
