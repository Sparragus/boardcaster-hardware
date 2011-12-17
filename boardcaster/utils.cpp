/*Copyright (C) 2011  Francisco De La Cruz, Gabriel J. Pérez
  and Richard B. Kaufman

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

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

// Show a string from PROGRAM
void showString (PGM_P s)
{
    char c;
    while ((c = pgm_read_byte(s++)) != 0)
        Serial.print(c, BYTE);
}

// Very rudimentary hardcoded board "emulator"
// Used for very simple "main loop" debugging
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

// Print the project banner
void showBanner()
{
    showString(PSTR("\nBoardcaster v1 - Fall 2011\n"));
    showString(PSTR("by Francisco De La Cruz\n"));
    showString(PSTR("..Richard B. Kaufman..\n"));
    showString(PSTR("..Gabriel J. Perez..\n"));
    showString(PSTR("..Daniel Gonzalez..\n"));
    showString(PSTR("..Carlos Andreu..\n"));
}

