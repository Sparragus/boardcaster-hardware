#ifndef _ATTACK_H
#define _ATTACK_H
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

#include "bitboard.h"

//Define directions
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define NO_WE 4
#define NO_EA 5
#define SO_WE 6
#define SO_EA 7

bitboard rookAttacks(bitboard*, int);
bitboard bishopAttacks(bitboard*, int);
bitboard queenAttacks(bitboard*, int);

#endif
