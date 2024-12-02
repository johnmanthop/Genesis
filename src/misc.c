#include <genesis.h>

#include "misc.h"

void clamp_point(struct Point *p, s16 lower_lim_x, s16 lower_lim_y, s16 upper_lim_x, s16 upper_lim_y)
{
    if (p->x < lower_lim_x) p->x = lower_lim_x;
    if (p->y < lower_lim_y) p->y = lower_lim_y;
    if (p->x > upper_lim_x) p->x = upper_lim_x;
    if (p->y > upper_lim_y) p->y = upper_lim_y;
}

/* branchless abs */
static inline u16 brl_abs(s16 v)
{
	u16 sign_ext = v >> 15;
	v ^= sign_ext;
	v += sign_ext & 1;

	return v;
}

/* Manhattan distance cause I can't get sqrt to work */
s16 distance(struct Point *a, struct Point *b)
{
	return brl_abs(a->x - b->x) + brl_abs(a->y - b->y);
}
