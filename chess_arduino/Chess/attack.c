
#include "bitboard.h"
#include "position.h"
#include "fen.h"

#include "attack.h"

// Function definitions

static void attack(bitboard*, int, int);
static void attack_north(bitboard*, int);
static void attack_south(bitboard*, int);
static void attack_east(bitboard*, int);
static void attack_west(bitboard*, int);
static void attack_nowe(bitboard*, int);
static void attack_noea(bitboard*, int);
static void attack_sowe(bitboard*, int);
static void attack_soea(bitboard*, int);

static bitboard diagonalAttacks(bitboard*, int);
static bitboard antiDiagAttacks(bitboard*, int);
static bitboard fileAttacks(bitboard*, int);
static bitboard rankAttacks(bitboard*, int);

static bitboard getPositiveRayAttacks(bitboard*, int, int);
static bitboard getNegativeRayAttacks(bitboard*, int, int);

static int bitScanForward(bitboard);
static int bitScanReverse(bitboard);

// ====

extern const bitboard _mask[64];

// ====

/*int main()*/
/*{*/
    /*char start_pos[] = "rnbqkbnr/pppppppp/8/8/8/8/PPP1PPPP/RNBQKBNR w KQkq - 0 1";*/
    /*position pos;*/

    /*init_bitboard();*/

    /*loadPositionFromFEN(start_pos, &pos);*/
    /*bitboard occupied = (pos.pieces[WHITE] | pos.pieces[BLACK]);*/

    /*[>printPosition(&pos);<]*/
    /*print(occupied);*/
    /*print( queenAttacks(&occupied, 4) );*/
    /*[>print( getPositiveRayAttacks(&occupied, NORTH, 4) );<]*/

    /*[>bitboard empty_bb = 0;<]*/
    /*[>attack_north(&empty_bb, 20);<]*/
    /*[>print( empty_bb );<]*/

    /*return 0;*/
/*}*/

// ====

bitboard rookAttacks(bitboard* occupied, int sq)
{
	return fileAttacks(occupied, sq) | rankAttacks(occupied, sq);
}

bitboard bishopAttacks(bitboard* occupied, int sq)
{
	return diagonalAttacks(occupied, sq) | antiDiagAttacks(occupied, sq);
}

bitboard queenAttacks(bitboard* occupied, int sq)
{
	return rookAttacks(occupied, sq) | bishopAttacks(occupied, sq);
}

// ====

static bitboard diagonalAttacks(bitboard* occupied, int sq) {
  return getPositiveRayAttacks(occupied, NO_EA, sq)
       | getNegativeRayAttacks(occupied, SO_WE, sq);
}

static bitboard antiDiagAttacks(bitboard* occupied, int sq) {
  return getPositiveRayAttacks(occupied, NO_WE, sq)
       | getNegativeRayAttacks(occupied, SO_EA, sq);
}

static bitboard fileAttacks(bitboard* occupied, int sq) {
  return getPositiveRayAttacks(occupied, NORTH, sq)
       | getNegativeRayAttacks(occupied, SOUTH, sq);
}

static bitboard rankAttacks(bitboard* occupied, int sq) {
  return getPositiveRayAttacks(occupied, EAST, sq)
       | getNegativeRayAttacks(occupied, WEST, sq);
}

// ====

static bitboard getPositiveRayAttacks(bitboard* occupied, int dir8, int square) {
    bitboard attacks = 0;
    attack(&attacks, dir8, square);

    bitboard blocker = attacks & *occupied;
    if ( blocker ) {
        square = bitScanForward(blocker);

        bitboard blocker_bb = 0;
        attack(&blocker_bb, dir8, square);

        attacks ^= blocker_bb;
    }
    return attacks;
}

static bitboard getNegativeRayAttacks(bitboard* occupied, int dir8, int square) {
    bitboard attacks = 0;
    attack(&attacks, dir8, square);

    bitboard blocker = attacks & *occupied;
    if ( blocker ) {
        square = bitScanReverse(blocker);

        bitboard blocker_bb = 0;
        attack(&blocker_bb, dir8, square);

        attacks ^= blocker_bb;
    }
    return attacks;
}

// ====

static int bitScanForward(bitboard blocker)
{
	int sq = 0;
	while( !(blocker & 1) )
	{
		blocker = blocker >> 1;
		sq++;
	}
	return sq;
}

static int bitScanReverse(bitboard blocker)
{
	int sq = 63;
	while( !(blocker & 0x8000000000000000LL) ) // 0x8000000000000000 has a '1' in the most significant bit of a 64 bit number
	{
		blocker = blocker << 1;
		sq--;
	}
	return sq;
}

// ====

static void attack(bitboard* attack_bb, int dir8, int square)
{
    switch(dir8){
        case NORTH:
            attack_north(attack_bb, square);
            break;

        case SOUTH:
            attack_south(attack_bb, square);
            break;

        case EAST:
            attack_east(attack_bb, square);
            break;

        case WEST:
            attack_west(attack_bb, square);
            break;

        case NO_EA:
            attack_noea(attack_bb, square);
            break;

        case NO_WE:
            attack_nowe(attack_bb, square);
            break;

        case SO_EA:
            attack_soea(attack_bb, square);
            break;

        case SO_WE:
            attack_sowe(attack_bb, square);
            break;

        default:
            break;
    }
}

static void attack_north(bitboard* bb, int sq)
{
	int index;

	for(index = sq + 8; (index/8) < 8; index = index + 8)
	{
		*bb = *bb | _mask[index];
	}
}

static void attack_south(bitboard* bb, int sq)
{
	int index;

	for(index = sq - 8; index >= 0; index = index - 8)
	{
		*bb = *bb | _mask[index];
	}
}

static void attack_east(bitboard* bb, int sq)
{
	int index;

	for(index = sq + 1; (index%8) != 0; index = index + 1)
	{
		*bb = *bb | _mask[index];
	}
}

static void attack_west(bitboard* bb, int sq)
{
	int index;

	for(index = sq - 1; ((index%8) != 7) && ((index%8) >= 0); index = index - 1)
	{
		*bb = *bb | _mask[index];
	}
}

static void attack_nowe(bitboard* bb, int sq)
{
	int index;

	for(index = sq + 7; ((index/8) < 8) && ((index%8) != 7); index = index + 7)
	{
		*bb = *bb | _mask[index];
	}
}

static void attack_noea(bitboard* bb, int sq)
{
	int index;

	for(index = sq + 9; ((index/8) < 8) && ((index%8) != 0); index = index + 9)
	{
		*bb = *bb | _mask[index];
	}
}

static void attack_sowe(bitboard* bb, int sq)
{
	int index;

	for(index = sq  - 9; (index >= 0) && ((index%8) != 7); index = index - 9)
	{
		*bb = *bb | _mask[index];
	}
}

static void attack_soea(bitboard* bb, int sq)
{
	int index;

	for(index = sq  - 7; (index >= 0) && ((index%8) != 0); index = index - 7)
	{
		*bb = *bb | _mask[index];
	}
}
