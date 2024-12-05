#ifndef ENEMY
#define ENEMY

#include <genesis.h>

#include "character.h"

#define MAX_ENEMIES 5

void enemies_init(struct Character enemies[], struct Room *grid);
void enemies_move(struct Character enemies[], struct Character *player);

#endif
