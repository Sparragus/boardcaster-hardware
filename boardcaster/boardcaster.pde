
#include "piece_detector.h"
#include "utils.h"
#include "hw_signals.h"
#include "bitboard_ops.h"

// Main firmware setup call
void setup()
{
  // Set serial transmission rate for debug prints
  Serial.begin(9600);
  
  // Initialize the piece detector
  initPieceDetector();
}

// Main firmware loop
void loop()
{
  // Scan piece array
  static uint64_t board = 0x0000000000000000LL;

  // Check for board changes
  // 1 = Board changed, 0 = No change
  if(scanPieceArray(&board) == 1)
    {
      // Boards Changed
      // Print the boards
      printBoard(&board,SENSOR_COUNT);
  
      // Run the Chess Engine
      //
      // void chessAnalyze()

      // Run the LED Array Code
      // 
      // void LEDArrayIllum()
    }
}
