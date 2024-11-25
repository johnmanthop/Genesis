#ifndef ROOM
#define ROOM

#include <genesis.h>

#include "room_res.h"
#include "misc.h"

#define ROOM_W 17
#define ROOM_H 11

enum ROOM_TILE
{
    TILE_BOX = 0,
    TILE_ENT = 4,
    TILE_B1 = 8,
    TILE_B2 = 12,
    TILE_B3 = 16,
    TILE_B4 = 20,
    TILE_BC1 = 24,
    TILE_BC2 = 28,
    TILE_BC4 = 32,
    TILE_BC3 = 36,
    TILE_FLOOR = 40
};

struct Room
{
    u8 vram_index;
    u8 room_descriptor[ROOM_H][ROOM_W];
};

extern struct Point grid_constructs[4][3];

void room_init(struct Room *r, u8 vram_index);
void room_create_random_grid(struct Room *r, u8 lim);
void room_display(const struct Room *r, u8 x, u8 y);

#endif