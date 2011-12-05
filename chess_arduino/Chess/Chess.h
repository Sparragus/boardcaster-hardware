#ifndef _CHESS_H_
#define _CHESS_H_
#include <avr/pgmspace.h>
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
