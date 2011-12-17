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
#include "led_disp.h"
#include "defines.h"

#include "piece_detector.h"
#include "bitboard_ops.h"
#include "utils.h"

// Display the letters B and C to test the display
// This is usually flashed upon successfully connecting to
// the Boardcaster website
void flashOK()
{
    uchar o_arr[] = {
        0,1,1,1,1,1,0,0,
        0,1,0,0,0,0,1,0,
        0,1,0,0,0,0,1,0,
        0,1,1,1,1,1,1,0,
        0,1,0,0,0,0,1,0,
        0,1,0,0,0,0,1,0,
        0,1,0,0,0,0,1,0,
        0,1,1,1,1,1,0,0,
    };
    uchar k_arr[] = {
        0,0,1,1,1,1,1,0,
        0,1,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,
        1,0,0,0,0,0,0,0,
        1,0,0,0,0,0,0,0,
        1,0,0,0,0,0,0,0,
        0,1,0,0,0,0,0,1,
        0,0,1,1,1,1,1,0,
    };
    uint64_t O;
    uint64_t K;
    
    // Make into bitboards
    arrayToBitBoard(o_arr, &O);
    arrayToBitBoard(k_arr, &K);
    
    // Flash the letters
    clearDisplay();
    displayPositions(&O);
    delay(1500);
    clearDisplay();
    displayPositions(&K);
    delay(1500);
    clearDisplay();
}

// Initialize the pins to be used for the shift registers
void initLedDisp() 
{
    //set pins to output so you can control the shift register
    pinMode(LA_DATA_PIN, OUTPUT);
    pinMode(LA_CLOCK_PIN, OUTPUT);
    pinMode(LA_LATCH_PIN, OUTPUT);
    pinMode(LA_XEN_PIN, OUTPUT);
  
    digitalWrite(LA_LATCH_PIN, HIGH);
}

// Shift out the 16bits in val over dataPin
// Toggle clockPin and use bitOrder first
void shiftOut16(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint16_t val)
{
    uint16_t i;
    for (i = 0; i < 16; i++) {
        if (bitOrder == LSBFIRST)
            digitalWrite(dataPin, !!(val & (1 << i)));
        else
            digitalWrite(dataPin, !!(val & (1 << (16 - i))));

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}


// This will turn on the given positions. A call to turnOffDisplay
// is necessarry after this call to turn off the positions.
void displayPositions(const uint64_t* inBoard)
{
    // Clear the display first
    clearDisplay();
   
    // Create a copy of the board 
    uint64_t inBoardNC = *inBoard;

    // Initialize the board parts as empty 
    uint16_t board_parts[4] = { 0x0FUL, 0x0FUL, 0x0FUL};

#ifdef MIRRORED_FILES
    // Use only if the hardware board is mirrored
    // This mirrors the output so that it is compatible
    // with the mirrored board. 
    mirrorBitboardX(&inBoardNC);
#endif
    // Set the board parts to serial out
    board_parts[0] = inBoardNC;
    board_parts[1] = (inBoardNC >> 16);
    board_parts[2] = (inBoardNC >> 32);
    board_parts[3] = (inBoardNC >> 48);

    // Set xenPin high to disable the drivers.
    // Set the latch low to allow data through latch. This might
    // have to be revised.
    digitalWrite(LA_XEN_PIN, HIGH);
    digitalWrite(LA_LATCH_PIN, LOW);

    // Set the clockPin low to prepare for rising edge trigger
    digitalWrite(LA_CLOCK_PIN, LOW);  

    // Shift out the data
    for(int i = 0; i < 4; i++)
    {
        shiftOut16(LA_DATA_PIN, LA_CLOCK_PIN, LSBFIRST, board_parts[i]);
    }
        
    // Set latch high to capture latch
    // Set xenPin low to enable the drivers
    // Set LA_LATCH_PIN low to allow data to pass through
    digitalWrite(LA_LATCH_PIN, HIGH);
    digitalWrite(LA_XEN_PIN, LOW);

    lockDisplay();

}

// Clear all data in shift registers to clear display
void clearDisplay()
{
    // Set xenPin high to disable the drivers.
    // Set the latch low to allow data through latch. This might
    // have to be revised.
    digitalWrite(LA_XEN_PIN, HIGH);
    digitalWrite(LA_LATCH_PIN, LOW);

    // Set the clockPin low to prepare for rising edge trigger
    digitalWrite(LA_CLOCK_PIN, LOW);  

    // Just shift out zeros
    for(int i = 0; i < 4; i++)
    {
        shiftOut16(LA_DATA_PIN, LA_CLOCK_PIN, LSBFIRST, 0);
    }
        
    // Set latch high to capture latch
    // Set xenPin low to enable the drivers
    // Set LA_LATCH_PIN low to allow data to pass through
    digitalWrite(LA_LATCH_PIN, HIGH);
    digitalWrite(LA_XEN_PIN, LOW);
  
    lockDisplay();
}

// Disable input to the shift registers
void lockDisplay()
{
    digitalWrite(LA_LATCH_PIN, HIGH);
}



