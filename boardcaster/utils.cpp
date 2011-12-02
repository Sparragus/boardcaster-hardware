#include "piece_detector.h"
#include "bitboard_ops.h"
#include "utils.h"
#include <WProgram.h>



// Convert linear position to 2D position
void linTo2D(uchar i, uchar* x, uchar* y)
{
  uchar yt = i/8;
  uchar xt = i%8;

  *x = xt;
  *y = yt;
}

void showString (PGM_P s)
{
        char c;
        while ((c = pgm_read_byte(s++)) != 0)
            Serial.print(c);
}



int emulate_board(uint64_t* in_board, int state)
{
    switch(state)
    {
        case 0:
        {
            uchar board[] = {
                1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                1,1,1,1,1,1,1,1,
                1,0,1,1,1,1,1,1
            };
            arrayToBitBoard(board, in_board);
            return 57;
            break;

        }
        case 1:

        {
                uchar board[] = {
                1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,1,0,0,0,0,0,
                1,1,1,1,1,1,1,1,
                1,0,1,1,1,1,1,1
            };
                arrayToBitBoard(board, in_board);
                return 42;



            break;
        }
    }
}

