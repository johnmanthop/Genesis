#include "enemies.h"

static u8 en_counters[MAX_ENEMIES];
static struct Room *grid = NULL;

void enemies_init(struct Character enemies[], struct Room *r)
{
	grid = r;

	for (u8 i = 0; i < MAX_ENEMIES; ++i)
	{
		character_init(&enemies[i]);

		s16 x = random() % ROOM_W;
		s16 y = random() % ROOM_H;
		
		while (r->room_descriptor[y][x] == TILE_BOX)
		{
			x = random() % ROOM_W;
			y = random() % ROOM_H;
		}
		x <<= 4;
		y <<= 4;
		character_set_position(&enemies[i], x, y);
		
		en_counters[i] = 0;
	}
}

void move_single_enemy(struct Character *en, struct Character *pl, u8 i)
{
	u16 d = distance(&en->position, &pl->position);
	
	if (d < 90)
	{
		struct Point en_p = en->position;
		struct Point pl_p = pl->position;
		
		struct Point direction_vector = {
			.x = (en_p.x - pl_p.x),
			.y = (en_p.y - pl_p.y)
		};
		
		// find dominant axis
		if (abs(direction_vector.x) > abs(direction_vector.y))
		{
			if (direction_vector.x < 0)
			{
				character_set_direction(en, RIGHT);
			}	
			else 	
			{
				character_set_direction(en, LEFT);
			}
		}
		else 
		{
			if (direction_vector.y < 0)
			{
				character_set_direction(en, DOWN);
			}
			else 
			{
				character_set_direction(en, UP);
			}
		}
	}
	else
	{
		if (en_counters[i] >= 40)
		{
			character_set_random_direction(en);
			en_counters[i] = 0;
		}
		else 
		{
			character_move_to_direction(en, grid);
			en_counters[i]++;
		}
	}
}

void enemies_move(struct Character enemies[], struct Character *pl)
{
	for (u8 i = 0; i < MAX_ENEMIES; ++i)
	{
		move_single_enemy(&enemies[i], pl, i);
	}
}
