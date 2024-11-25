#ifndef MISC
#define MISC

struct Point
{
    s16 x, y;
};

void clamp_point(struct Point *p, u8 lower_lim_x, u8 lower_lim_y, u8 upper_lim_x, u8 upper_lim_y);

#endif