// Code by Gabriel J. Perez
//         Francisco De La Cruz
#include <WProgram.h>
#include "led_disp.h"
#include "defines.h"

#include "piece_detector.h"
#include "bitboard_ops.h"
void initLedDisp() 
{
    //set pins to output so you can control the shift register
    pinMode(LA_DATA_PIN, OUTPUT);
    pinMode(LA_CLOCK_PIN, OUTPUT);
    pinMode(LA_LATCH_PIN, OUTPUT);
    pinMode(LA_XEN_PIN, OUTPUT);
  
    digitalWrite(LA_LATCH_PIN, HIGH);
}

/*  Split bitboard into 4 segments of an array 
    array. The returned pointer is to static data which is overwritten with each call*/

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
    clearDisplay();
   
    uint16_t board_parts[4] = { 0x0FUL, 0x0FUL, 0x0FUL};
    uint64_t tBoard =0x0FULL;
    mirrorBitboardX(&tBoard);
    
    board_parts[0] = tBoard;
    board_parts[1] = (tBoard >> 16);
    board_parts[2] = (tBoard >> 32);
    board_parts[3] = (tBoard >> 48);

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
    
//  lockDisplay();
}
void clearDisplay()
{
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
        shiftOut16(LA_DATA_PIN, LA_CLOCK_PIN, LSBFIRST, 0);
    }
        
    // Set latch high to capture latch
    // Set xenPin low to enable the drivers
    // Set LA_LATCH_PIN low to allow data to pass through
    digitalWrite(LA_LATCH_PIN, HIGH);
    digitalWrite(LA_XEN_PIN, LOW);
  
   lockDisplay();
}

void lockDisplay()
{
 
   digitalWrite(LA_LATCH_PIN, HIGH);
}



