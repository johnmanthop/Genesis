#include <genesis.h>

#include "room.h"
#include "map.h"

int main(bool hard)
{
    VDP_loadTileSet(&room_tileset, 1, DMA);

    PAL_setPalette(PAL1, room_palette.data, DMA);

    struct Room r;

    room_init(&r, 1);
    room_create_random_grid(&r, 20);

    room_display(&r, 3, 3);

    while (1)
    {
        // wait for screen refresh
        SYS_doVBlankProcess();
    }

    return 0;
}