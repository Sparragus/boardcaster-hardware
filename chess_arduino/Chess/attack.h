#ifndef _ATTACK_H
#define _ATTACK_H

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
