#include <WProgram.h>
#include "piece_detector.h"
#include "bitboard_ops.h"
#define NDEBUG
// Compare board1 against board2 for the specified amount of sensors
// Under normal operation SENSOR_COUNT = SCAN_SIZE
// Return: -1 = Equal boards
// Return: >= 0 = Different boards; Square that is different.
int compareBoards(uint64_t* board1, uint64_t* board2)
{
    unsigned int i;
    int ret = -1;
    for(i = 0; i < SENSOR_COUNT; i++)
    {
        if(getBit(board1, i)!= getBit(board2, i))
        {
            ret = i;
        }
    }
    return ret;
}

// Prints a bitboard up to n positions
void printBoard(uint64_t* board, int n)
{
    unsigned int i;
    Serial.print("[");
    for(i = 0; i < n && i < SCAN_SIZE; i++)
    {
        if(n > 8 && i%8 == 0)
            Serial.println("");
        Serial.print(getBit(board,i), DEC);
        if(i+1 != n && i != SCAN_SIZE)
            Serial.print(", ");
    }
    Serial.println("]");
}

// Convert array of board into a bitboard
void arrayToBitBoard(uchar* array, uint64_t* board)
{
    uint64_t temp = 0LL;
    int i;
    for(i = 0; i < SCAN_SIZE; i++)
    {
        if(array[63-i] == 1)
        {
            temp |= 1LL<<i;
        }
    }
    *board = temp;
}

// Get bit from board
uchar getBit(uint64_t* board, uchar bit)
{
    unsigned long int res = 0L;
    uint64_t hi  = (*board >> 32) & 0x00000000FFFFFFFFULL;
    uint64_t lo =  *board & 0x00000000FFFFFFFFULL;

    if(bit < 31)
        res = (hi >> (31-bit)) & 1L;
    else
    {
        bit -=32;
        res = (lo >> (31-bit)) & 1L;
    }
    return res;
}

// Set bit to data of board.
void putBit(uint64_t* board, uchar data, uchar bit)
{
    uint64_t board_hi = (*board >> 32)  & 0x00000000FFFFFFFFULL;
    uint64_t  board_lo = *board & 0x00000000FFFFFFFFULL;

    if(data == 0)
    {
        if(bit >= 0 && bit < 32)
        {
            board_hi = board_hi &  ~(1L<<(31-bit));
        }
        else if(bit >=32 && bit < 64)
        {
            bit -= 32;
            board_lo &= ~(1L<<(31-bit));
        }
    }
    else if (data == 1)
    {
        if(bit >= 0 && bit < 32)
        {
            board_hi = board_hi | (1L<<(31-bit));
        }
        else if(bit >=32 && bit < 64)
        {
            bit -= 32;
            board_lo |= (1L<<(31-bit));
        }
    }

    *board  = board_lo | (board_hi << 32);

    // Assert the bits. This should NEVER assert false
    if (getBit(board, bit) != data)
    {
#ifdef DEBUG
        Serial.print("Got: ");
        Serial.print(getBit(board, bit), BIN);
        Serial.print(" Expected: ");
        Serial.print(data, BIN);
        Serial.println(" Assert setting bit!");
#endif
    }
}

