#include "cub3d.h"

void set_player_pos(int x, int y) {
	if (map_terrain(x, state.__py) == terrain_positive_space || map_terrain(x, state.__py) == terrain_door)
		state.__px = x;

	if (map_terrain(state.__px, y) == terrain_positive_space || map_terrain(state.__px, y) == terrain_door)
		state.__py = y;
}
