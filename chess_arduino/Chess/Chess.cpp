#ifdef __cplusplus

extern "C" {
#endif
#include "bitboard.h"
#ifdef __cplusplus
}
#endif

#include "position.h"
#include "fen.h"
#include "move.h"
#include "Chess.h"
#include "WProgram.h"

#include <avr/pgmspace.h>


extern const bitboard _mask[64];




Chess::Chess()
{
    Chess("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Chess::Chess(char FEN[])
{
    init_bitboard();

    memset(moves, 0, STORE_SIZE);
    clearPosition(&pos);

    loadPositionFromFEN(FEN, &pos);

}

bitboard Chess::getPieceMoves(const int sq_source)
{

    //Init all moves to 0;
    memset(moves, 0, STORE_SIZE*sizeof(move));
 
    int player = pos.toPlay;
    int piece = getPieceToPlay(sq_source);
    int numMoves = 0;
    numMoves += getMoves(&pos, player, piece, NORMAL, &moves[numMoves]);
    numMoves += getMoves(&pos, player, piece, CAPTURE, &moves[numMoves]);

    bitboard realMoves = 0;
    realMoves = getRealMoves(moves, sq_source, numMoves);
    return realMoves;
}

// Returns:
// 0 = Legal Move
// 1 = Illegal Move
int Chess::playPieceMove(int sq_dest)
{
    //get move that goes to sq_dest
    int i;
    for(i=0; i<STORE_SIZE; i++)
    {
        //If the move goes to where we want...
        if(moves[i].to == sq_dest)
        {
            playMove(&pos, &pos, &moves[i], pos.toPlay);
            return 0;
        }
    }

    // There was no move to play.
    return 1;
}

bitboard Chess::getCurrentPosition()
{
    bitboard b = pos.pieces[WHITE]|pos.pieces[BLACK];
    //  printBitboard(&b);

    return (b);
}

void Chess::printBitboard(const bitboard* bb)
{
    int i;

    for(i = 63; i >=0; i--) {
        if(*bb & _mask[i]) {
            Serial.print('1');
        }
        else {
            Serial.print('0');
        }

        if(i % 8 == 0) {
            Serial.print('\n');
        }
    }

    Serial.print('\n');
}

bitboard Chess::getMask(const int sq)
{
    return _mask[sq];
}

char* Chess::getFENFromPosition()
{
    static char fen[256];
    savePositionToFEN(&pos, fen);
    return fen;
}

void Chess::printOwnPosition()
{
    printPosition(&pos);
}

void Chess::printPosition(const position* pos)
{
    int sq;
    char rank;
    char file;
    char castle[5] = "----";

    for(sq = 63; sq >= 0; sq--) {
        if(WHITE_KING == pos->board[sq]) {
            showString(PSTR("K"));
        }
        else if(BLACK_KING == pos->board[sq]) {
            showString(PSTR("k"));
        }
        else if(WHITE_QUEEN == pos->board[sq]) {
            showString(PSTR("Q"));
        }
        else if(BLACK_QUEEN == pos->board[sq]) {
            showString(PSTR("q"));
        }
        else if(WHITE_ROOK == pos->board[sq]) {
            showString(PSTR("R"));
        }
        else if(BLACK_ROOK == pos->board[sq]) {
            showString(PSTR("r"));
        }
        else if(WHITE_BISHOP == pos->board[sq]) {
            showString(PSTR("B"));
        }
        else if(BLACK_BISHOP == pos->board[sq]) {
            showString(PSTR("b"));
        }
        else if(WHITE_KNIGHT == pos->board[sq]) {
            showString(PSTR("N"));
        }
        else if(BLACK_KNIGHT == pos->board[sq]) {
            showString(PSTR("n"));
        }
        else if(WHITE_PAWN == pos->board[sq]) {
            showString(PSTR("P"));
        }
        else if(BLACK_PAWN == pos->board[sq]) {
            showString(PSTR("p"));
        }
        else if(0 == pos->board[sq]) {
            showString(PSTR("-"));
        }
        else {
        }

        /* fputc(' ', stderr); */

        if(sq % 8 == 0) {
            if(56 == sq) {
                if(WHITE == pos->toPlay) {
                    showString(PSTR("[White]"));
                }
                else {
                    showString(PSTR("[Black]"));
                }
            }
            else if(48 == sq) {
                if(pos->epSquare != -1) {
                    rank = RANK_NOTATION(pos->epSquare);
                    file = FILE_NOTATION(pos->epSquare);

                    showString(PSTR("[")); Serial.print(file); Serial.print(rank); showString(PSTR("]"));
                }
                else {
                    showString(PSTR("[-]"));
                }               
            }
            else if(40 == sq) {
                if(pos->castleFlags & CASTLE_WK) {
                    castle[0] = 'K';
                }

                if(pos->castleFlags & CASTLE_WQ) {
                    castle[1] = 'Q';
                }

                if(pos->castleFlags & CASTLE_BK) {
                    castle[2] = 'k';
                }

                if(pos->castleFlags & CASTLE_BQ) {
                    castle[3] = 'q';
                }

                showString(PSTR("[")); Serial.print(castle); showString(PSTR("]"));

            }

            showString(PSTR("\n"));
        }
    }
    showString(PSTR("\n"));
}


 






int Chess::getPieceToPlay(int sq_source)
{
    if(pos.king[pos.toPlay] & _mask[sq_source])
    {
        if(pos.toPlay == WHITE) {return WHITE_KING;}
        else {return BLACK_KING;}
    }
    else if(pos.queens[pos.toPlay] & _mask[sq_source])
    {
        if(pos.toPlay == WHITE) {return WHITE_QUEEN;}
        else {return BLACK_QUEEN;}
    }
    else if(pos.rooks[pos.toPlay] & _mask[sq_source])
    {
        if(pos.toPlay == WHITE) {return WHITE_ROOK;}
        else {return BLACK_ROOK;}
    }
    else if(pos.bishops[pos.toPlay] & _mask[sq_source])
    {
        if(pos.toPlay == WHITE) {return WHITE_BISHOP;}
        else {return BLACK_BISHOP;}
    }
    else if(pos.knights[pos.toPlay] & _mask[sq_source])
    {
        if(pos.toPlay == WHITE) {return WHITE_KNIGHT;}
        else {return BLACK_KNIGHT;}
    }
    else if(pos.pawns[pos.toPlay] & _mask[sq_source])
    {
        if(pos.toPlay == WHITE) {return WHITE_PAWN;}
        else {return BLACK_PAWN;}
    }
    else {return 0;} //SHOULD NEVER GET HERE. Piece is unknown.
}

bitboard Chess::getRealMoves(const move moves[], int sq_source, int numMoves)
{
    int i;
    bitboard realMoves=0;
    for(i=0; i<numMoves; i++)
    {
        //If the move comes from where we want...
        if(moves[i].from == sq_source)
        {
            // ...add it's destination as a possible move.
            realMoves |= _mask[moves[i].to];
        }
    }

    return realMoves;
}


void Chess::showString (PGM_P s)
{
    char c;
    while ((c = pgm_read_byte(s++)) != 0)
        Serial.print(c, BYTE);
}

