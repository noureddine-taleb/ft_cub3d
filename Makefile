MINILIBX_DIR := minilibx
MINILIBX := $(MINILIBX_DIR)/libmlx.a
TARGET := cub3d
SRCS := main.c cub3d.c window.c map.c player.c
HDRS := cub3d.h
CFLAGS := -I $(MINILIBX_DIR) -lm -framework OpenGL -framework AppKit # -Wall -Wextra -Werror

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS) $(MINILIBX)
	$(CC) $(CFLAGS) $(SRCS) $(MINILIBX) -o $@

$(MINILIBX): $(MINILIBX_DIR)
	$(MAKE) -C $^

clean:
	rm -f *.o

fclean: clean
	rm $(TARGET)

re: fclean all
