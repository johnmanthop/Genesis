#include "bullet.h"

static void check_bullet_collisions(struct Bullet *b)
{

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
	if (b->frames_active >= B_LIM)
	{
		SPR_releaseSprite(b->sp);
		b->sp = NULL;
	}
	else
	{
		check_bullet_collisions(b);
	}
}
