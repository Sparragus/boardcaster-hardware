/*
AshChess - A simple and stupid computer chess program
Copyright (C) 2005 Ashwin Phatak

  Version 2.0 - Adapted for the Boardcaster's Chess Engine
  @Author: Richard B. Kaufman-Lopez <richardbkaufman [at] gmail [dot] com>

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

#ifndef _BITBOARD_H_
#define _BITBOARD_H_

#define LSB_SET(x) ((x) & 1)
#define SET_BIT(x, y) (x |= _mask[(y)])
#define CLR_BIT(x, y) (x &= ~_mask[(y)])

#define RANK_STATE(b, rank) (((b) >> ((rank) << 3)) & 0xff)
#define FILE_STATE(rotb, file) (( (rotb) >> ((file) << 3)) & 0xff)


#define SHIFT 0
#define MASK 1

#define A1H8_STATE(rotb, sq) ((rotb >> _a1h8_shiftMask[sq][SHIFT]) & _a1h8_shiftMask[sq][MASK])
#define H1A8_STATE(rotb, sq) ((rotb >> _h1a8_shiftMask[sq][SHIFT]) & _h1a8_shiftMask[sq][MASK])

/* 64-bit unsigned data type */
typedef unsigned long long bitboard;

/* Init the internal bitboards */
void init_bitboard(void);

// returns bitboard with moves in all directions for the king
bitboard i_king(int sq);

// returns bitboard with moves in all legal directions for the knight
bitboard i_knight(int sq);

#endif

