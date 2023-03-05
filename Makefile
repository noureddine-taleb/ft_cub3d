MINILIBX_DIR := minilibx
MINILIBX := $(MINILIBX_DIR)/libmlx.a
TARGET := cub3d
SRCS := main.c cub3d.c window.c raycaster.c map.c player.c texture.c sprite.c math.c
HDRS := cub3d.h
# TODO: remove debugging instruments
CFLAGS := -I $(MINILIBX_DIR) -lm -framework OpenGL -framework AppKit -g -fsanitize=address -fno-omit-frame-pointer # -Wall -Wextra -Werror

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
