#include <genesis.h>

#include "bullet.h"
#include "room.h"
#include "character.h"
#include "bullet.h"
#include "enemies.h"

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

void intro_wait()
{
    VDP_drawText("Press A to start!", 12, 10);

    bool exit = false; 
    while (!exit)
    {
        if (fire) exit = true;

        // here the player is tricked into making a random room/grid ;)
        setRandomSeed(random()); 

        SPR_update();
        SYS_doVBlankProcess();
    }

}

int main(bool hard)
{
    struct Room r;
    struct Character ch;
	struct Character enemies[MAX_ENEMIES];

    SPR_init();
    JOY_init();
    JOY_setEventHandler(&joystick_callback);
	PAL_setPalette(PAL1, room_palette.data, DMA);
    
    intro_wait();

	room_init(&r, 1);
    room_create_random_grid(&r, 20);
    room_display(&r, 3, 3);

	character_init(&ch);
	
	populate_grid_info(&r);

	enemies_init(enemies, &r);

    while (1)
    {
		enemies_move(enemies, &ch);
        handle_player_input(&ch, &r, player_v_x, player_v_y, fire, 1);        
		
        character_tick_bullets(&ch, &r);
        character_check_health_zero(&ch);

        for (u8 i = 0; i < MAX_ENEMIES; ++i)
		{
			character_tick_bullets(&enemies[i], &r);
		    
            if (enemies[i].sp != NULL) character_check_health_zero(&enemies[i]);
        }

        bullet_check_hits(&ch, enemies);
    
        bool pl_lost = (ch.sp == NULL);
        bool pl_won  = true;
        for (u8 i = 0; i < MAX_ENEMIES; ++i)
        {
            if (enemies[i].sp != NULL) pl_won = false;
        }

        if (pl_lost)
        {
            VDP_drawText("You Lost! :(", 15, 10);
            
            SPR_update();
            SYS_doVBlankProcess();
            for (;;);
        } 
        else if (pl_won)
        {
            VDP_drawText("You Won:! :)", 15, 10);
            
            SPR_update();
            SYS_doVBlankProcess();
            for (;;);
        }

		// wait for screen refresh
        SPR_update();
        SYS_doVBlankProcess();
    }

    return 0;
}
