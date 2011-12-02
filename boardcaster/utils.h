#ifndef UTILS_H
#define UTILS_H
#include <avr/pgmspace.h>
void linTo2D(uchar i, uchar* x, uchar* y);
void showString (PGM_P s);
// No-Board testing function.
int emulate_board(uint64_t* in_board, int state);



#endif //

