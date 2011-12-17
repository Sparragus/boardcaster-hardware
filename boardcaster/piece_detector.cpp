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
#include "utils.h"
#include "hw_signals.h"
#include "bitboard_ops.h"
#include "defines.h"
#include "led_disp.h"


uint64_t old_board = 0x0000000000000000LL;
// Just settle for 1ms

const long unsigned  TIME_SETTLE = 1;
// Benchmark the Scan

long unsigned realTimeToScan = 0;

// Illuminate all leds in a zigzag pattern

void cycleArray()
{
    // Start with a clear board
    uint64_t dboard = 0x0ULL;

    // Set traversal direction
    // + = right , - = left
    int dir = 1;

    // Bit position
    int bitPos = 0;
    int p = 0;

    for(int j = 0; j < 8; j++)
    {
        bitPos = p;
        for(int i = 0; i < 8; i++)
        { 
            putBit(&dboard, 1, bitPos);
            delay(30);
            displayPositions(&dboard);
            delay(100);
            bitPos += dir;
        }
        // Change direction for each rank
        dir = -dir;
        if(j%2==0) 
            p+=15; // Move to the opposite side
        else
            p+=1; // Stay on the same side
    } 
}


// Scan the board into the long long board (64 bits)
// Return: 1 = Board Change
//       : 0 = No Board Change
int scanPieceArray(uint64_t* board)
{
    // Disable the interrupts
    noInterrupts();

    // Save old board
    old_board = *board;
 
    // Read the board as uchars into tboard
    uchar tboard[SCAN_SIZE];
    
    long start_time, end_time = 0;
    uchar x, y = 0;

    // Scan the board
    // Run i from 0 to 63
    for(unsigned int i = 0; i < SCAN_SIZE; i++)
    {
        linTo2D(i, &x, &y);

        sig_t col;
        sig_t row;

        // Generate device signals  
        generateSig(x, &col);
        generateSig(y, &row);

        // Decoder = Row Iterator
        // Multiplexer = Column Iterator
        // One multiplexer per RANK

        // Enable Decoder
        setDecoder(&row);

        // Enable Multiplexer
        setMux(&col);

        // Wait for settle
        delay(TIME_SETTLE);
    
        // Read Result
        uchar data = readPieceArrayLine();
        data = digitalRead(PD_OUT_DATA);

        tboard[i] = data;
    }
 
    // Convert array bit board into a long long 
    arrayToBitBoard(tboard, board);

    // Reenable the interrupts
    interrupts();

    // Assert conversion failure
    // This should NEVER happen.
    if(tboard[0] != getBit(board, 0) && tboard[1] != getBit(board, 1))
        Serial.print("getBitFailure");

#ifdef DEBUG
    Serial.print("NEW BOARD ");
    printBoard(board, SENSOR_COUNT);
    Serial.print("OLD BOARD ");
    printBoard(&old_board, SENSOR_COUNT);
    Serial.print("Full compare: ");
    Serial.print(old_board == *board, BIN);
    Serial.println("");
#endif
    return compareBoards(board, &old_board);
}

// Initialize the Piece Detector
void initPieceDetector()
{
    // Set up pin directions
    pinMode(PD_DEC_PA0, OUTPUT);
    pinMode(PD_DEC_PA1, OUTPUT);
    pinMode(PD_DEC_PA2, OUTPUT);
    pinMode(PD_MUX_PA, OUTPUT);
    pinMode(PD_MUX_PB, OUTPUT);
    pinMode(PD_MUX_PC, OUTPUT);

    // Set output pin
    pinMode(PD_OUT_DATA, INPUT);

    // Disable internal pullup
    digitalWrite(PD_OUT_DATA, LOW);

    // Delay for a while (100ms)
    delay(100);
  
    // Record start
    unsigned long int startBench = millis();

    // Sweep the array
    uchar x, y = 0;
    for(unsigned int i = 0; i < SCAN_SIZE; i++)
    {
        linTo2D(i, &x, &y);

        sig_t col;
        sig_t row;

        // Generate device signals  
        generateSig(x, &col);
        generateSig(y, &row);

        // Enable Decoder
        setDecoder(&row);

        // Enable Multiplexer
        setMux(&col);
     
        // Wait for settle
        delay(TIME_SETTLE); 
     
        // Read the data but do nothing;
        readPieceArrayLine();
    }

    // Record end time
    realTimeToScan = millis() - startBench;
    Serial.print("  [");
    Serial.print(realTimeToScan, DEC);
    Serial.print("]ms/scan..");
}


