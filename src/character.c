#include "character.h"

void character_init(struct Character *ch)
{
    ch->position.x = 40; ch->position.y = 40;

    ch->sp = SPR_addSprite(&char_sprite, ch->position.x, ch->position.y, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE, 0));
    SPR_setAnim(ch->sp, 1);
}

void handle_player_input(struct Character *ch, s8 v_x, s8 v_y)
{
    ch->position.x += v_x;
    ch->position.y += v_y;
    SPR_setPosition(ch->sp, ch->position.x, ch->position.y);

    if (v_x > 0)
    {
        SPR_setAnim(ch->sp, 2);
    }
    else if (v_x < 0)
    {
        SPR_setAnim(ch->sp, 1);
    }
    else if (v_y < 0)
    {
        SPR_setAnim(ch->sp, 3);
    }
    else if (v_y > 0)
    {
        SPR_setAnim(ch->sp, 0);
    }
    else 
    {
        // SPR_setFrame(ch->sp, 0);
    }
}