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

#ifndef BITBOARD_OPS_H
#define BITBOARD_OPS_H

void arrayToBitBoard(uchar* array, uint64_t* board);
void printBoard(uint64_t* board, int n);
int compareBoards(uint64_t* board1, uint64_t* board2);

// Bit Operations
void putBit(uint64_t* board, uchar data, uchar bit);
uchar getBit(uint64_t* board, uchar bit);
void mirrorBitboardX(uint64_t* board);
#endif //BITBOARD_OPS_H

