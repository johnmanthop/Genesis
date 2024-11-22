#include <genesis.h>
#include "map.h"

int main(bool hard)
{
    //VDP_drawText("alaiz", 10, 10);

    PAL_setPalette(PAL0, palette_all.data, DMA);

    u16 ind = TILE_USER_INDEX;
    VDP_loadTileSet(&level_tileset, ind, DMA);
    ind += level_tileset.numTile;

    Map *bga = MAP_create(&level_map, BG_A, TILE_ATTR_FULL(0, FALSE, FALSE, FALSE, TILE_USER_INDEX));

    u32 offset = 0;
    while (1)
    {
        MAP_scrollTo(bga, offset, offset);
        // wait for screen refresh
        SYS_doVBlankProcess();
    }

    return 0;
}