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
#include <assert.h>

#include "position.h"
#include "move.h"
#include "fen.h"
#include "diag.h"
#include "bitboard.h"


static move piece_ID(const position * const pos, bitboard lifted_pos);
static void piece_thisPiece(const position * const pos, const bitboard * const lifted_pos, move * m);
static void piece_from(bitboard lifted_pos, move * m);

int main(void)
{

    char start_pos[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    char end_pos[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1";
    position pos_01;
    position pos_02;

    init();

    loadPositionFromFEN(start_pos, &pos_01);
    printPosition(&pos_01);

    loadPositionFromFEN(end_pos, &pos_02);
    printPosition(&pos_02);

    bitboard lifted_pos = pos_02.pieces[WHITE] | pos_02.pieces[BLACK];

    move m = piece_ID(&pos_01, lifted_pos);

    move _move_store[64][256];

    int colour = COLOUR(m.thisPiece);
    int piece = m.thisPiece;
    int from = m.from;

    bitboard legal_moves = getRawMoves(&pos_01, colour, piece, NORMAL, from);
    legal_moves |= getRawMoves(&pos_01, colour, piece, CAPTURE, from);

    print(legal_moves);

    return 0;
}

// Returns int that identifies piece and color. See position.h for details
static move piece_ID(const position * const pos, bitboard lifted_pos)
{
    bitboard all_pieces = (pos->pieces[WHITE] | pos->pieces[BLACK]);
    lifted_pos = all_pieces ^ lifted_pos;

    move m;

    // Determine piece and colour. Stored in m.thisPiece
    piece_thisPiece(pos, &lifted_pos, &m);

    // Determine where the piece came from. Stored in m.from
    piece_from(lifted_pos, &m);

    return m;
}

// Changes move field m.thisPiece.
static void piece_thisPiece(const position * const pos, const bitboard * const lifted_pos, move * m)
{

    //Check WHITE pieces
    if(pos->pieces[WHITE] & *lifted_pos)
    {
        if(pos->king[WHITE] & *lifted_pos)
        {
            m->thisPiece = WHITE_KING;

        }
        else if(pos->queens[WHITE] & *lifted_pos)
        {
            m->thisPiece = WHITE_QUEEN;

        }
        else if(pos->rooks[WHITE] & *lifted_pos)
        {
            m->thisPiece = WHITE_ROOK;

        }
        else if(pos->bishops[WHITE] & *lifted_pos)
        {
            m->thisPiece = WHITE_BISHOP;

        }
        else if(pos->knights[WHITE] & *lifted_pos)
        {
            m->thisPiece = WHITE_KNIGHT;

        }
        else if(pos->pawns[WHITE] & *lifted_pos)
        {
            m->thisPiece = WHITE_PAWN;

        }
        else
        {
            // I don't know what piece this is!
            // Shouldn't reach here.
            assert(0);
        }

    }
    //Check BLACK pieces
    else
    {
        if(pos->king[BLACK] & *lifted_pos)
        {
            m->thisPiece = BLACK_KING;

        }
        else if(pos->queens[BLACK] & *lifted_pos)
        {
            m->thisPiece = BLACK_QUEEN;

        }
        else if(pos->rooks[BLACK] & *lifted_pos)
        {
            m->thisPiece = BLACK_ROOK;

        }
        else if(pos->bishops[BLACK] & *lifted_pos)
        {
            m->thisPiece = BLACK_BISHOP;

        }
        else if(pos->knights[BLACK] & *lifted_pos)
        {
            m->thisPiece = BLACK_KNIGHT;

        }
        else if(pos->pawns[BLACK] & *lifted_pos)
        {
            m->thisPiece = BLACK_PAWN;

        }
        else
        {
            // I don't know what piece this is!
            // Shouldn't reach here.
            assert(0);
        }
    }//end else if BLACK
}

// Determines where the piece came from. Stored in m->from
static void piece_from(bitboard lifted_pos, move * m)
{
    int sq = 0;
    while(lifted_pos != 0)
    {
        if( LSB_SET(lifted_pos) )
        {
            m->from = sq;
        }

        lifted_pos >>= 1;
        sq++;
    }
}
