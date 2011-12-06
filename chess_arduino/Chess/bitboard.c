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

#include "bitboard.h"

/* Internal bitboards */
bitboard _mask[64];
/*bitboard _king[64];*/
/*bitboard _knight[64];*/
bitboard _wpawn_advance1[64];
bitboard _bpawn_advance1[64];
bitboard _wpawn_advance2[64];
bitboard _bpawn_advance2[64];
bitboard _wpawn_attack[64];
bitboard _bpawn_attack[64];

/* These functions are not needed by anyone outside the file */
static void init_mask(void);
/*static void init_king(void);*/
/*static void init_knight(void);*/
static void init_pawns(void);

void init_bitboard(void)
{
    init_mask();
    // init_king();
    // init_knight();
    init_pawns();
}

static void init_mask(void)
{
    bitboard b = 1;
    int i;

    for(i = 0; i < 64; i++) {
        _mask[i] = b;
        b = b << 1;
    }
}

bitboard i_king(int sq)
{
    bitboard temp = 0;
    int i;
    int file;
    int rank;
    sq++;
    for(i = 0; i < sq; i++) {
        temp = 0;

        file = i % 8;
        rank = i / 8;

        /* left */
        if(file < 7) {
            temp |= _mask[i] << 1;
        }

        /* right */
        if(file > 0) {
            temp |= _mask[i] >> 1;
        }

        /* up */
        if(rank < 7) {
            temp |= _mask[i] << 8;
        }

        /* down */
        if(rank > 0) {
            temp |= _mask[i] >> 8;
        }

        /* left up */
        if(file < 7 && rank < 7) {
            temp |= _mask[i] << 9;
        }

        /* left down */
        if(file < 7 && rank > 0) {
            temp |= _mask[i] >> 7;
        }

        /* right up */
        if(file > 0 && rank < 7) {
            temp |= _mask[i] << 7;
        }

        /* right down */
        if(file > 0 && rank > 0) {
            temp |= _mask[i] >> 9;
        }


        // _king[i] = temp;

    }

    return temp;
}
abcd;
bitboard i_knight(int sq)
{
    bitboard temp = 0;
    int i;
    int file;
    int rank;
    
    sq++;
    for(i = 0; i < sq; i++) {
        temp = 0;

        file = i % 8;
        rank = i / 8;

        /* left side */

        if(file < 6 && rank < 7) {
            temp |= _mask[i] << 10;
        }

        if(file < 7 && rank < 6) {
            temp |= _mask[i] << 17;
        }

        if(file < 6 && rank > 0) {
            temp |= _mask[i] >> 6;
        }

        if(file < 7 && rank > 1) {
            temp |= _mask[i] >> 15;
        }



        /* right side */

        if(file > 1 && rank < 7) {
            temp |= _mask[i] << 6;
        }


        if(file > 0 && rank < 6) {
            temp |= _mask[i] << 15;
        }

        if(file > 1 && rank > 0) {
            temp |= _mask[i] >> 10;
        }

        if(file > 0 && rank > 1) {
            temp |= _mask[i] >> 17;
        }

        /*_knight[i] = temp;*/
    }

    return temp;
}

static void init_pawns(void)
{
    int sq;
    int file;

    /* white pawn advances (hard to resist?) */
    for(sq = 8; sq < 56; sq++) {
        _wpawn_advance1[sq] = _mask[sq] | (_mask[sq] << 8);
        if(sq < 16) {
            _wpawn_advance2[sq] = _mask[sq] << 16;
        }
    }

    /* black pawn advances */
    for(sq = 55; sq >= 8; sq--) {
        _bpawn_advance1[sq] = _mask[sq] | (_mask[sq] >> 8);
        if(sq >= 48) {
            _bpawn_advance2[sq] = _mask[sq] >> 16;
        }
    }

    /* white pawn captures */
    for(sq = 8; sq < 56; sq++) {
        _wpawn_attack[sq] = _mask[sq];
        file = sq % 8;
        if(file > 0) {
            _wpawn_attack[sq] |= _mask[sq] << 7;
        }
        if(file < 7) {
            _wpawn_attack[sq] |= _mask[sq] << 9;
        }
    }

    /* black pawn captures */
    for(sq = 55; sq >= 8; sq--) {
        _bpawn_attack[sq] = _mask[sq];
        file = sq % 8;
        if(file > 0) {
            _bpawn_attack[sq] |= _mask[sq] >> 9;
        }
        if(file < 7) {
            _bpawn_attack[sq] |= _mask[sq] >> 7;
        }
    }
}
