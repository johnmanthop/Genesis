#ifndef CHARACTER
#define CHARACTER

#include <genesis.h>
#include "misc.h"
#include "room.h"
#include "character_res.h"
#include "bullet.h"

#define PL_OFFSET_Y 25
#define PL_OFFSET_X 25
#define MAX_ACTIVE_BULLETS 8

struct Character
{
    struct Bullet bullets[MAX_ACTIVE_BULLETS];

    struct Point position;
    enum DIR direction;
    Sprite *sp;
    u8 health;
    u8 vram_index;
};

void character_init         (struct Character *ch);
void handle_player_input    (struct Character *ch, struct Room *grid, s8 v_x, s8 v_y, u8 fire);
void character_tick_bullets (struct Character *ch, struct Room *grid);

#endif
