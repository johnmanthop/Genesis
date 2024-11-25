#include "character.h"

void character_init(struct Character *ch)
{
    ch->position.x = 40; ch->position.y = 40;

    ch->sp = SPR_addSprite(&char_sprite, ch->position.x, ch->position.y, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
    SPR_setAnim(ch->sp, 1);
}

void handle_player_input(struct Character *ch, struct Room *grid, s8 v_x, s8 v_y)
{
    u16 r_x = ch->position.x - 40;
    u16 r_y = ch->position.y - 40;
    if (r_x >= ROOM_W) r_x = ROOM_W - 1;
    if (r_y >= ROOM_H) r_y = ROOM_H - 1;
    
    char debug[512];
    sprintf(debug, "%d %d\n", r_x >> 4, r_y >> 4);
    KLog(debug);

    if (v_x)
    {
        SPR_setAnim(ch->sp, (v_x > 0)? 2 : 1);

        if (grid->room_descriptor[r_y >> 4][(r_x >> 4) + 1] == TILE_BOX)
        {
            if ((r_x >> 4) == ((r_x + v_x) >> 4))
            {
                ch->position.x += v_x;
                SPR_setPosition(ch->sp, ch->position.x, ch->position.y);
            }
        }
        else 
        {
            ch->position.x += v_x;
            SPR_setPosition(ch->sp, ch->position.x, ch->position.y);
        }
    }
    else if (v_y)
    {
        SPR_setAnim(ch->sp, (v_y < 0)? 3 : 0);

        if (grid->room_descriptor[(r_y >> 4) + 1][r_x >> 4] == TILE_BOX)
        {
            //if (((r_y + v_y) >> 4) == (r_y >> 4))
            {
                ch->position.y += v_y;
                SPR_setPosition(ch->sp, ch->position.x, ch->position.y);
            }
        }
        else 
        {
            ch->position.y += v_y;
            SPR_setPosition(ch->sp, ch->position.x, ch->position.y);
        }
    }
    else 
    {
        // SPR_setFrame(ch->sp, 0);
    }
}