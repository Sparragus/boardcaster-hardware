/*Copyright (C) 2011  Francisco De La Cruz, Gabriel J. Pérez
  and Richard B. Kaufman

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include <WProgram.h>
#include "piece_detector.h"
#include "bitboard_ops.h"

// Undefine to enable asserts.
// DO not undefine when running production code.
#define NDEBUG

// Compare board1 against board2 for the specified amount of sensors
// Under normal operation SENSOR_COUNT = SCAN_SIZE
// Return: -1 = Equal boards
// Return: >= 0 = Different boards; Returned value equals
//                                  Square that is different.
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

// Mirrors bitboard in place.
// After call file A is where file H was
void mirrorBitboardX(uint64_t *iboard)
{
    uint64_t mboard = 0x0ULL;
    
    uchar bit = 0;
    uchar xpos = 0;

    // Mirror de board
    for(int j = 0; j < 8; j++)
    {
        for(int i = 0; i < 8; i++)
        {
            xpos = (j*8)+(7-i);
            bit = getBit(iboard, xpos);
            putBit(&mboard, bit, j*8+i);
        }
    }
   
    *iboard = mboard;
}

// Prints a bitboard up to n positions
void printBoard(uint64_t* board, int n)
{
    unsigned int i;
    uint64_t temp_board = *board;
    Serial.print("[");
    for(i = 0; i < n && i < SCAN_SIZE; i++)
    {
        if(n > 8 && i%8 == 0)
            Serial.println("");
        Serial.print(getBit(&temp_board,i), DEC);
        if(i+1 != n && i != SCAN_SIZE)
            Serial.print(", ");
    }
    Serial.println("]");
}

// Convert array of board into a bitboard
void arrayToBitBoard(uchar* array, uint64_t* board)
{
    // Start with a 0 bitboard
    uint64_t temp = 0LL;
    int i;
    // Shift bits into place where a 1 value is
    // found
    for(i = 0; i < SCAN_SIZE; i++)
    {
        if(array[63-i] == 1)
        {
            temp |= 1ULL<<i;
        }
    }
   
    *board = temp;
}

// Get bit from board
uchar getBit(uint64_t* board, uchar bit)
{
    // Split boards into high-word low-words
    // Bitwise shifting is not defined for 64bit integers
    unsigned long int res = 0L;
    uint64_t hi  = (*board >> 32) & 0x00000000FFFFFFFFULL;
    uint64_t lo =  *board & 0x00000000FFFFFFFFULL;
   
    // Check for boundary crossing
    if(bit <= 31)
        res = (hi >> (31-bit)) & 1ULL;
    else
    {
        bit -=32;
        res = (lo >> (31-bit)) & 1ULL;
    }
   
    return res;
}

// Set bit to data of board.
void putBit(uint64_t* iboard, uchar data, uchar bit)
{
    // Split boards into high-word low-words
    // Bitwise shifting is not defined for 64bit integers 
    uint64_t board_hi = (*iboard >> 32)  & 0x00000000FFFFFFFFULL;
    uint64_t  board_lo = *iboard & 0x00000000FFFFFFFFULL;
    
    // The following code is overly verbose
    // for clarity.
    if(data == 0) // Clearing data
    {
        if(bit >= 0 && bit < 32)
        {
            board_hi = board_hi &  ~(1ULL<<(31-bit));
        }
        else if(bit >=32 && bit < 64)
        {
            bit -= 32;
            if(bit == 0) // Is this the boundary?
                board_lo = board_lo & ~(1ULL<<31);
            else
                board_lo = board_lo & ~(1ULL<<(31-bit));
        }
    }
    else if (data == 1) // Setting data.
    {
        if(bit >= 0 && bit < 32)
        {
            board_hi = board_hi | (1ULL<<(31-bit));
        }
        else if(bit >=32 && bit < 64)
        {
            bit -= 32;
            if(bit == 0) // Is this the boundary?
            {
                board_lo = board_lo | ( 1ULL<<31);
            }
            else
                board_lo = board_lo | (1ULL<<(31-bit));
        }
    }
  
    *iboard  = (board_hi << 32) | board_lo;
  
// For debugging Purposes
    // Assert the bits. This should NEVER assert false
#ifdef DEBUG
    if (getBit(iboard, bit) != data)
    {
    Serial.print("Got: ");
    Serial.print(getBit(iboard, bit), BIN);
    Serial.print(" Expected: ");
    Serial.print(data, BIN);
    Serial.println(" Assert setting bit!");
}
#endif
}

