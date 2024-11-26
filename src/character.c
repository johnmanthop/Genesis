#include "character.h"

void character_init(struct Character *ch)
{
    ch->position.x = 0; ch->position.y = 0;

    ch->sp = SPR_addSprite(&char_sprite, ch->position.x + PL_OFFSET_X, ch->position.y + PL_OFFSET_Y, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
    SPR_setAnim(ch->sp, 1);
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

void handle_player_input(struct Character *ch, struct Room *grid, s8 v_x, s8 v_y)
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

    if (v_x > 0)        
    {
        SPR_setAnim(ch->sp, 2);
        if (ch->position.x + 16 >= (ROOM_W << 4) - 1) return;
    }
    else if (v_x < 0)   
    {
        SPR_setAnim(ch->sp, 1);
        if (ch->position.x <= 0) return;
    }
    else if (v_y > 0)
    {
        SPR_setAnim(ch->sp, 0);
        if (ch->position.y + 16 >= (ROOM_H << 4) - 2) return;
    }
    else if (v_y < 0)
    {
        SPR_setAnim(ch->sp, 3);
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