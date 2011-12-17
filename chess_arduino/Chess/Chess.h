#ifndef _CHESS_H_
#define _CHESS_H_
#include <avr/pgmspace.h>
/*
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

 @Author: Richard B. Kaufman-Lopez <richardbkaufman [at] gmail [dot] com>
 */

class Chess
{

public:

    Chess();
    Chess(char FEN[]);
    bitboard getPieceMoves(const int sq_source);
    int playPieceMove(int sq_dest);
    bitboard getCurrentPosition();
    bitboard getMask(const int sq);
    char* getFENFromPosition();

    void printBitboard(const bitboard* bb);
    void printPosition(const position* pos);
    void printOwnPosition();
private:
    static const int STORE_SIZE = 64;

    position pos;
    move moves[STORE_SIZE];

    int getPieceToPlay(int sq);
    bitboard getRealMoves(const move moves[], int sq_source, int numMoves);
    void showString(PGM_P s);
};

#endif
