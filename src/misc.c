#include <genesis.h>

#include "misc.h"

void clamp_point(struct Point *p, u8 lower_lim_x, u8 lower_lim_y, u8 upper_lim_x, u8 upper_lim_y)
{
    if (p->x < lower_lim_x) p->x = lower_lim_x;
    if (p->y < lower_lim_y) p->y = lower_lim_y;
    if (p->x > upper_lim_x) p->x = upper_lim_x;
    if (p->y > upper_lim_y) p->y = upper_lim_y;
}
