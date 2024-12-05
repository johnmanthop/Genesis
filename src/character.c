#include "character.h"

static u8 last_frame_fire = 0;
static enum DIR direction_mapping[4] = { LEFT, RIGHT, UP, DOWN };

void character_init(struct Character *ch)
{
    ch->health          = 100;
    ch->position.x      = 0; 
    ch->position.y      = 0;
    ch->direction       = LEFT;
    
   	ch->sp = SPR_addSprite(&char_sprite, ch->position.x + PL_OFFSET_X, ch->position.y + PL_OFFSET_Y, TILE_ATTR(PAL1, FALSE, FALSE, FALSE));
    SPR_setAnim(ch->sp, LEFT);
	
	for (u8 i = 0; i < MAX_ACTIVE_BULLETS; ++i)
	{
		ch->bullets[i].sp = NULL;
	}
}

void character_fire(struct Character *ch, u8 i, enum DIR d)
{	
	ch->bullets[i].frames_active = 0;
    ch->bullets[i].position    = ch->position;
	ch->bullets[i].position.x  += 4;
	ch->bullets[i].position.y  += 4;
    ch->bullets[i].direction   = d;
    
	ch->bullets[i].sp          = SPR_addSprite(&bullet_sprite, 
                                                ch->bullets[i].position.x + PL_OFFSET_X, 
                            					ch->bullets[i].position.y + PL_OFFSET_Y, 
                                                TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
}

void character_set_random_direction(struct Character *ch)
{
	ch->direction = direction_mapping[random() % 4];
}

void character_set_direction(struct Character *ch, enum DIR d)
{
	ch->direction = d;
	SPR_setAnim(ch->sp, d);
}

void character_set_position(struct Character *ch, s16 x, s16 y)
{
	ch->position.x = x;
	ch->position.y = y;
	SPR_setPosition(ch->sp, ch->position.x + PL_OFFSET_X, ch->position.y + PL_OFFSET_Y);
}

void character_move_to_direction(struct Character *ch, struct Room *grid)
{
	u8 v_x = 0, v_y = 0;

	switch (ch->direction)
	{
		case LEFT: 	v_x = -1; break;
		case RIGHT: v_x =  1; break;
		case UP:	v_y = -1; break;
		case DOWN:  v_y =  1; break;	
	}

	handle_player_input(ch, grid, v_x, v_y, 0, 0);
}

void character_move(struct Character *ch, s16 x, s16 y)
{
	ch->position.x += x;
	ch->position.y += y;
	SPR_setPosition(ch->sp, ch->position.x + PL_OFFSET_X, ch->position.y + PL_OFFSET_Y);
}

static bool is_legal_move(struct Room *grid, u16 x, u16 y, s8 v_x, s8 v_y)
{
    if (v_x)
    {
        s8 grid_offset = (v_x > 0) ? 1 : (-1);
        s8 pixel_offset = (v_x > 0) ? 1 : (-1);

        if (grid->room_descriptor[y >> 4][(x >> 4) + grid_offset] == TILE_BOX)
        {
            // if the player tile position + a small delta is still the same tile, the player can move
            return ((x >> 4) == ((x + pixel_offset) >> 4));
        }
        else 
        {
            return true;
        }
    }
    else if (v_y)
    {
        s8 grid_offset = (v_y > 0) ? 1 : (-1);
        s8 pixel_offset = (v_y > 0) ? 1 : (-1);

        if (grid->room_descriptor[(y >> 4) + grid_offset][x >> 4] == TILE_BOX)
        {
            // if the player tile position + a small delta is still the same tile, the player can move
            return ((y >> 4) == ((y + pixel_offset) >> 4));
        }
        else 
        {
            return true;
        }
    }
    else 
    {
        return false;
    }
}

void handle_player_input(struct Character *ch, struct Room *grid, s8 v_x, s8 v_y, u8 fire, u8 player_flag)
{
    // top left
    u16 x1 = ch->position.x + 2;
    u16 y1 = ch->position.y + 2;

    // top right
    u16 x2 = x1 + 13;
    u16 y2 = y1;

    // bot left;
    u16 x3 = x1;
    u16 y3 = y1 + 13;
    // bot right
    u16 x4 = x1 + 13;
    u16 y4 = y1 + 13; 

    if (fire && !last_frame_fire)
    {
		for (u8 i = 0; i < MAX_ACTIVE_BULLETS; ++i)
		{
			if (ch->bullets[i].sp == NULL)
			{
        		last_frame_fire = 1;
				character_fire(ch, i, ch->direction);
				break;
			}
		}
    }
    else if (!fire && player_flag) last_frame_fire = 0;

    if (v_x > 0)        
    {
        ch->direction = RIGHT;
        SPR_setAnim(ch->sp, RIGHT);
        if (ch->position.x + 16 >= (ROOM_W << 4) - 1) return;
    }
    else if (v_x < 0)   
    {
        ch->direction = LEFT;
        SPR_setAnim(ch->sp, LEFT);
        if (ch->position.x <= 0) return;
    }
    else if (v_y > 0)
    {
        ch->direction = DOWN;
        SPR_setAnim(ch->sp, DOWN);
        if (ch->position.y + 16 >= (ROOM_H << 4) - 2) return;
    }
    else if (v_y < 0)
    {
        ch->direction = UP;
        SPR_setAnim(ch->sp, UP);
        if (ch->position.y <= 0) return;
    }

    bool is_legal_move_hitbox = is_legal_move(grid, x1, y1, v_x, v_y) &&
                                is_legal_move(grid, x2, y2, v_x, v_y) &&
                                is_legal_move(grid, x3, y3, v_x, v_y) &&
                                is_legal_move(grid, x4, y4, v_x, v_y);

    if (is_legal_move_hitbox)
    {
        ch->position.x += v_x;
        ch->position.y += v_y;
        SPR_setPosition(ch->sp, ch->position.x + PL_OFFSET_X, ch->position.y + PL_OFFSET_Y);
    }
}


void character_tick_bullets(struct Character *ch, struct Room *grid)
{
    for (u8 i = 0; i < MAX_ACTIVE_BULLETS; ++i)
    {
		if (ch->bullets[i].sp != NULL) 
		{
			set_bullet_state(&ch->bullets[i]);
		}
	}

	for (u8 i = 0; i < MAX_ACTIVE_BULLETS; ++i)
	{
		if (ch->bullets[i].sp != NULL)
		{
			move_bullet(&ch->bullets[i]);
		}
	}
}
