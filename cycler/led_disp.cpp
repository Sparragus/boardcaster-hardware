// Code by Gabriel J. Perez
//         Francisco De La Cruz
#include <WProgram.h>
#include "led_disp.h"
#include "defines.h"



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
uint16_t *getParts(uint64_t* board)
{

    static uint16_t board_parts[4];
    board_parts[0] = *board;
    board_parts[1] = (*board >> 16);
    board_parts[2] = (*board >> 32);
    board_parts[3] = (*board >> 48);

    return board_parts;
}

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
void displaypositions(uint16_t* positions)
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
        shiftOut16(LA_DATA_PIN, LA_CLOCK_PIN, LSBFIRST, positions[i]);
    }
        
    // Set latch high to capture latch
    // Set xenPin low to enable the drivers
    // Set LA_LATCH_PIN low to allow data to pass through
    digitalWrite(LA_LATCH_PIN, HIGH);
    digitalWrite(LA_XEN_PIN, LOW);

}

// Turn off the display, only to be called after displaypositions
void turnOffDisplay()
{
    digitalWrite(LA_LATCH_PIN, LOW);
}


