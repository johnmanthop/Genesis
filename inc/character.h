#ifndef CHARACTER
#define CHARACTER

#include <genesis.h>
#include "misc.h"
#include "room.h"
#include "character_res.h"

struct Character
{
    struct Point position;
    Sprite *sp;
    u8 health;
    u8 vram_index;
};

void character_init     (struct Character *ch);
void handle_player_input(struct Character *ch, struct Room *grid, s8 v_x, s8 v_y);

#endif