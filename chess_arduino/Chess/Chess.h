#ifndef _CHESS_H_
#define _CHESS_H_

class Chess
{

public:

    Chess();
    Chess(char FEN[]);
    bitboard getPieceMoves(const int sq_source);
    int playPieceMove(int sq_dest);
    bitboard getCurrentPos();
    bitboard getMask(const int sq);
    char[] getFENFromPos();

    void printBitboard(const bitboard* bb);
    void printPosition(const position* pos);

private:
    static const int STORE_SIZE = 64;

    position pos;
    move moves[STORE_SIZE];

    int getPieceToPlay(int sq);
    bitboard getRealMoves(const move moves[], int sq_source, int numMoves);

};

#endif
