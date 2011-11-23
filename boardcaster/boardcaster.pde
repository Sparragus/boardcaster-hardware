#include "piece_detector.h"
#include "led_disp.h"
#include "poster.h"
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

  // Initialize the LED array
  initLedDisp();

  // Init web posting code
  initPoster();
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

      /* Some code to demnostrate how to integrate with LED module */
      /* if (piece_is_up) */
      /* { */
      /* 	uint16_t parts  = getParts(&positions_board); */
      /* 	display_positions(&parts); */
      /* 	boolean diplayingPositions = true; */
      /* } */

      /* if (!piece_is_up && displayingPositions) */
      /* { */
      /* 	turnOffDisplay(); */
      /* }  */

      /* if (display_error) */
      /* { */
      /* 	uint16_t parts  = getParts(&error_board); */
      /* 	display_positions(&parts); */
      /* 	delay(100); */
      /* 	turnOffDisplay(); */
      /* } */

      /* if (sending_fen) */
      /* { */
      /* 	setNextFEN(fenstring); */
      /* 	sendData(); */
      /* } */
    }
}
