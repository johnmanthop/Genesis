#include <genesis.h>

#include "room.h"
#include "character.h"

s8 player_v_x       = 0;
s8 player_v_y       = 0;
u8 fire             = 0;

void joystick_callback(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        fire = (state & BUTTON_A);
        
        if (state & BUTTON_RIGHT)
        {
            player_v_x = 1;
            player_v_y = 0;
        }
        else if (state & BUTTON_LEFT)
        {
            player_v_x = -1;
            player_v_y = 0;
        }
        else if (state & BUTTON_UP)
        {
            player_v_x = 0;
            player_v_y = -1;
        }
        else if (state & BUTTON_DOWN)
        {
            player_v_x = 0;
            player_v_y = 1;
        }
        else 
        {
            player_v_x = 0;
            player_v_y = 0;
        }
    }
}

int main(bool hard)
{
    struct Room r;
    struct Character ch;

    SPR_init();
    JOY_init();
    JOY_setEventHandler(&joystick_callback);
	PAL_setPalette(PAL1, room_palette.data, DMA);
    
	room_init(&r, 1);
    room_create_random_grid(&r, 20);
    room_display(&r, 3, 3);
    character_init(&ch);

    while (1)
    {
        handle_player_input(&ch, &r, player_v_x, player_v_y, fire);
        character_tick_bullets(&ch);
        // wait for screen refresh
        SPR_update();
        SYS_doVBlankProcess();
    }

    return 0;
}
