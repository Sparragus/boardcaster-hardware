#include "piece_detector.h"
#include "led_disp.h"
//#include "poster.h"
#include "utils.h"
#include "hw_signals.h"
#include "bitboard_ops.h"
#include "led_disp.h"
#include "piece_detector.h"

// Main firmware setup call
void setup()
{
    delay(1000);
    // Set serial transmission rate for debug prints
    Serial.begin(9600);

    Serial.println("Initializing LED Array");
    // Initialize the LED array
    initLedDisp();

    Serial.println("Cycling LED array, please wait...");
    // Run LED diagnostics
    cycleArray();

    Serial.println("Cycle done.. ");

    // Piece is placed, turn off leds
     turnOffDisplay();
}

// Main firmware loop
void loop()
{
    static uint64_t board = 0x0000000000000000LL;

    // Check for board changes
    // 1 = Board changed, 0 = No change
    scanPieceArray(&board);
    uint16_t* parts  = getParts(&board);
    displaypositions(parts);
    delay(50);
    turnOffDisplay();

}


