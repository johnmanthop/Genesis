#ifndef BULLET
#define BULLET

#include <genesis.h>
#include "misc.h"
#include "room.h"

#define B_SPEED     2
#define B_LIM       45
#define PL_OFFSET_X 25
#define PL_OFFSET_Y 25

enum DIR 
{
    UP = 3, 
    DOWN = 0, 
    LEFT = 1, 
    RIGHT = 2
};

struct Bullet
{
    Sprite *sp;
    enum DIR direction;
    struct Point position;
    u16 frames_active;
};

void set_bullet_state	(struct Bullet *b);
void move_bullet		(struct Bullet *b);
void populate_grid_info	(struct Room *r);

#endif
