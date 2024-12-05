#include "enemies.h"
#include "bullet.h"

static u8 box_counter = 0;
static struct Point box_positions[ROOM_H * ROOM_W];

static void del_bullet(struct Bullet *b)
{
    SPR_releaseSprite(b->sp);
	b->sp = NULL;
}

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

void bullet_move(struct Bullet *b)
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


void bullet_check_hits(struct Character *pl, struct Character *enemies)
{
    // first player hits
    for (u8 i = 0; i < MAX_ACTIVE_BULLETS; ++i)
    {
        if (pl->bullets[i].sp == NULL) continue;

        struct Point *bp = &pl->bullets[i].position;
        for (u8 j = 0; j < MAX_ENEMIES; ++j)
        {
            struct Point *ep = &enemies[j].position;
            
            if (bp->x >= ep->x && bp->x <= ep->x + 16 &&
                bp->y >= ep->y && bp->y <= ep->y + 16)
            {
                enemies[j].health -= 20;
                del_bullet(&pl->bullets[i]);
            }
        }
    }
    
    struct Point *pp = &pl->position;

    for (u8 j = 0; j < MAX_ENEMIES; ++j)
    {
        if (enemies[j].sp == NULL) continue;

        for (u8 i = 0; i < MAX_ACTIVE_BULLETS; ++i)
        {
            if (enemies[j].bullets[i].sp == NULL) continue;

            struct Point *bp = &enemies[j].bullets[i].position;
            
            if (bp->x >= pp->x && bp->x <= pp->x + 16 &&
                bp->y >= pp->y && bp->y <= pp->y + 16)
            {
                pl->health -= 20;
                del_bullet(&enemies[j].bullets[i]);
            }

        }
    }
}

void bullet_set_state(struct Bullet *b, u8 b_lim)
{
	if (b->frames_active >= b_lim || check_bullet_collisions(b))
	{
		// maybe play a sound clip
        del_bullet(b);
	}
}
