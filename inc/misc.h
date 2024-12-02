#ifndef MISC
#define MISC

struct Point
{
    s16 x, y;
};

void clamp_point(struct Point *p, s16 lower_lim_x, s16 lower_lim_y, s16 upper_lim_x, s16 upper_lim_y);

s16 distance(struct Point *a, struct Point *b);

#endif
