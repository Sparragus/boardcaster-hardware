#include "piece_detector.h"
// Convert linear position to 2D position
void linTo2D(uchar i, uchar* x, uchar* y)
{
    uchar yt = i/8;
    uchar xt = i%8;

    *x = xt;
    *y = yt;
}

