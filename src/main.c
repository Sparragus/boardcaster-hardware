/*
AshChess - A simple and stupid computer chess program
Copyright (C) 2005 Ashwin Phatak

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <stdio.h>
#include "position.h"
#include "move.h"
#include "fen.h"
#include "diag.h"
#include "bitboard.h"

int main(void)
{

    char start_pos[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    position pos;
    position newPos;

    init();

    loadPositionFromFEN(start_pos, &pos);
    printPosition(&pos);

    move _move_store[64][256];

    int numMoves = getMoves(&pos, WHITE, WHITE_PAWN, NORMAL, _move_store[0]);

    printf("%d\n\n", numMoves);

    if( 0 == playMove(&pos, &newPos, &_move_store[0][2], WHITE))
            printPosition(&newPos);

    return 0;
}

