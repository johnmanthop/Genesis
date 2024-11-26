#include "room.h"

struct Point grid_constructs[4][3] = {
    { {  .x = 0, .y = 0 }, { .x = 0, .y = 1 }, { .x = 1,  .y = 1 } },
    { {  .x = 0, .y = 0 }, { .x = 0, .y = 1 }, { .x = -1, .y = 1 } },
    { {  .x = 0, .y = 0 }, { .x = 0, .y = 1 }, { .x = 0,  .y = 2 } },
    { {  .x = 0, .y = 0 }, { .x = 1, .y = 0 }, { .x = 2,  .y = 0 } }
};

void room_init(struct Room *r, u8 vram_index)
{
    VDP_loadTileSet(&room_tileset, vram_index, DMA);

    r->vram_index = vram_index;

    for (u8 i = 0; i < ROOM_H; ++i)
    {
        for (u8 j = 0; j < ROOM_W; ++j)
        {
            r->room_descriptor[i][j] = TILE_FLOOR;
        }
    }

    for (u8 i = 0; i < ROOM_H; ++i)
    {
        r->room_descriptor[i][0] = TILE_B1;
        r->room_descriptor[i][ROOM_W - 1] = TILE_B2; 
    }

    for (u8 j = 0; j < ROOM_W; ++j)
    {
        r->room_descriptor[0][j] = TILE_B3;
        r->room_descriptor[ROOM_H - 1][j] = TILE_B4; 
    }

    r->room_descriptor[0][0]                    = TILE_BC1;
    r->room_descriptor[0][ROOM_W - 1]           = TILE_BC2;
    r->room_descriptor[ROOM_H - 1][0]           = TILE_BC3;
    r->room_descriptor[ROOM_H - 1][ROOM_W - 1]  = TILE_BC4;
}

void room_create_random_grid(struct Room *r, u8 lim)
{
    for (u8 i = 0; i < lim; ++i)
    {
        struct Point construct[3];
        u8 index = random() % 4; // random construct index
        
        for (u8 j = 0; j < 3; ++j)
        {
            construct[j] = grid_constructs[index][j];
            construct[j].x += random() % (ROOM_W - 1) + 1;
            construct[j].y += random() % (ROOM_H - 1) + 1;

            clamp_point(&construct[j], 0, 0, ROOM_W - 1, ROOM_H - 1);

            r->room_descriptor[construct[0].y][construct[0].x] = TILE_BOX;
            r->room_descriptor[construct[0].y][construct[0].x] = TILE_BOX;
            r->room_descriptor[construct[0].y][construct[0].x] = TILE_BOX;
        }
    }

    r->room_descriptor[(random() % ROOM_H - 1) + 1][(random() % ROOM_W - 1) + 1] = TILE_ENT;
}

void room_display(const struct Room *r, u8 x, u8 y)
{
    /* The boxes *should* to be drawn at a different plane */
    PAL_setPalette(PAL1, room_palette.data, DMA);
    
    for (u8 i = 0; i < ROOM_H; ++i)
    {
        for (u8 j = 0; j < ROOM_W; ++j)
        {
            u8 vram_offset = r->room_descriptor[i][j];

            VDP_fillTileMapRectInc(BG_A, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, r->vram_index + vram_offset), 
                                                x + (j << 1), y + (i << 1), 2, 2);
        }
    }
}