#include "character.h"

void character_init(struct Character *ch)
{
    ch->position.x = 0; ch->position.y = 0;

    ch->sp = SPR_addSprite(&char_sprite, ch->position.x + PL_OFFSET_X, ch->position.y + PL_OFFSET_Y, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
    SPR_setAnim(ch->sp, 1);
}

void handle_player_input(struct Character *ch, struct Room *grid, s8 v_x, s8 v_y)
{
    // r_x and r_y are the player's coordinates transormed at the center of the sprite
    u16 r_x = ch->position.x + 8;
    u16 r_y = ch->position.y + 8;

    if (v_x < 0 && r_x == 0) return;
    if (v_x > 0 && r_x + 16 == ROOM_W << 4) return;

    if (v_x)
    {
        SPR_setAnim(ch->sp, (v_x > 0)? 2 : 1);

        s8 grid_offset  = (v_x > 0)? 1 : (-1);
        s8 pixel_offset = (v_x > 0)? 8 : (-8);

        // if the next tile to the dirrection of movement is a box
        if (grid->room_descriptor[r_y >> 4][(r_x >> 4) + grid_offset] == TILE_BOX)
        {
            // if the player tile position + a small delta is still the same tile, the player can move
            if ((r_x >> 4) == ((r_x + pixel_offset) >> 4))
            {
                ch->position.x += v_x;
                SPR_setPosition(ch->sp, ch->position.x + PL_OFFSET_X, ch->position.y + PL_OFFSET_Y);
            }
        }
        else 
        {
            ch->position.x += v_x;
            SPR_setPosition(ch->sp, ch->position.x + PL_OFFSET_X, ch->position.y + PL_OFFSET_Y);
        }
    }
    else if (v_y)
    {
        SPR_setAnim(ch->sp, (v_y < 0)? 3 : 0);

        s8 grid_offset  = (v_y > 0)? 1 : (-1);
        s8 pixel_offset = (v_y > 0)? 8 : (-8);

        if (grid->room_descriptor[(r_y >> 4) + grid_offset ][r_x >> 4] == TILE_BOX)
        {
            if (((r_y + pixel_offset) >> 4) == (r_y >> 4))
            {
                ch->position.y += v_y;
                SPR_setPosition(ch->sp, ch->position.x + PL_OFFSET_X, ch->position.y + PL_OFFSET_Y);
            }
        }
        else 
        {
            ch->position.y += v_y;
            SPR_setPosition(ch->sp, ch->position.x + PL_OFFSET_X, ch->position.y + PL_OFFSET_Y);
        }
    }
    else 
    {
        // SPR_setFrame(ch->sp, 0);
    }
}