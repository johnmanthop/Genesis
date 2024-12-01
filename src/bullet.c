#include "bullet.h"

static u8 box_counter = 0;
static struct Point box_positions[ROOM_H * ROOM_W];

static bool check_bullet_collisions(struct Bullet *b)
{
	struct Point bul_p = b->position;
	bul_p.x += 4;
	bul_p.y += 4;
	
	if (bul_p.x <= 2 || 
		bul_p.y <= 2 || 
		bul_p.x + 4 >= (ROOM_W << 4) || 
		bul_p.y + 4 >= (ROOM_H << 4)) 
			return true;

	for (u8 i = 0; i < box_counter; ++i)
	{
		struct Point box_p = box_positions[i];

		if (bul_p.x >= box_p.x && bul_p.x <= box_p.x + 16 &&
			bul_p.y >= box_p.y && bul_p.y <= box_p.y + 16)
		{
			// bullet has hit a box
			return true;
		}
	}	
	
	return false;
}

void populate_grid_info(struct Room *r)
{
	for (u8 i = 0; i < ROOM_H; ++i)
	{
		for (u8 j = 0; j < ROOM_W; ++j)
		{
			if (r->room_descriptor[i][j] == TILE_BOX)
			{
				box_positions[box_counter].x = (j << 4);
				box_positions[box_counter].y = (i << 4);
				box_counter++;
			}
		}
	}
}	

void move_bullet(struct Bullet *b)
{		
    switch (b->direction)
    {
        case UP:    b->position.y -= B_SPEED; break;
       	case DOWN:  b->position.y += B_SPEED; break;
       	case LEFT:  b->position.x -= B_SPEED; break;
      	case RIGHT: b->position.x += B_SPEED; break;
    }

	SPR_setPosition(b->sp, b->position.x + PL_OFFSET_X, b->position.y + PL_OFFSET_Y);
    b->frames_active++;
}

void set_bullet_state(struct Bullet *b)
{
	if (b->frames_active >= B_LIM || check_bullet_collisions(b))
	{
		// maybe play a sound clip
		SPR_releaseSprite(b->sp);
		b->sp = NULL;
	}
}
