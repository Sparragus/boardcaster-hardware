#ifndef BITBOARD_OPS_H
#define BITBOARD_OPS_H
void arrayToBitBoard(uchar* array, uint64_t* board);
void printBoard(uint64_t* board, int n);
int compareBoards(uint64_t* board1, uint64_t* board2);

// Bit Operations
void putBit(uint64_t* board, uchar data, uchar bit);
uchar getBit(uint64_t* board, uchar bit);

#endif //BITBOARD_OPS_H

