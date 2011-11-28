// Chess Engine <START>
#include <bitboard.h>
#include <position.h>
#include <move.h>
#include <fen.h>
#include <attack.h>
#include <Chess.h>
// Chess Engine <END>

#include "boardcaster.h"
#include "piece_detector.h"
#include "led_disp.h"
//#include "poster.h"
#include "utils.h"
#include "hw_signals.h"
#include "bitboard_ops.h"
#include <stdlib.h>

Chess chess;

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};

void * operator new(size_t size)
{
 return malloc(size);
}

void operator delete(void * ptr)
{
 free(ptr);
}



// Main firmware setup call
void setup()
{
    // Set serial transmission rate for debug prints
    Serial.begin(9600);
    // Initialize the piece detector
    initPieceDetector();

    // Initialize the LED array
    initLedDisp();

    // Run LED diagnostics
    cycleArray();

    // Init web posting code
    //initPoster();

    // Init chess engine
//    chess = Chess("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    chess = Chess("4k3/8/8/8/4Q3/8/8/4K3 w KQkq - 0 1");
}

// Main firmware loop
void loop()
{
    // Get current position
    bitboard currentPosition;
    currentPosition = chess.getCurrentPosition();
    static uint64_t board = currentPosition;

    // Scan piece array
    /*static uint64_t board = 0x0000000000000000LL;*/

    // Scan piece array until a change is detected
    // sq >= 0 if Board changed; Square that changed, sq = -1 = No change
    int sq_source;
    do
    {
        sq_source = scanPieceArray(&board);
    }
    while(sq_source == -1);

    // Obtain a bitboard with the legal moves for a piece on the square sq
    bitboard moves;
    moves = chess.getPieceMoves( sq_source );


    // Turn on LEDs using moves
    uint16_t* parts  = getParts(&moves);
    displaypositions(parts);


    // Scan piece array until a change is detected
    // sq_source >= 0 if Board changed; Square that changed, sq_source = -1 = No change
    int sq_dest;
    do
    {
        sq_dest = scanPieceArray(&board);
    }
    while(sq_dest == -1);

    // Piece is placed, turn off leds
    turnOffDisplay();

    // If sq_source == sq_dest, then piece was placed back to it's original pos
    // Don't play the move. Loop again.
    if(sq_source == sq_dest)
    {
        //TODO: check if empty return is safe.
        return;
    }

    uint64_t error_board = 0;
    // legal == 0 if move is legal, else legal == 1, meaning move is illegal
    // while move is illegal...
    while(chess.playPieceMove(sq_dest) != 0)
    {
         if( sq_dest >= 0 )
         {
            error_board = chess.getMask(sq_dest);
         }
         uint16_t* parts  = getParts(&error_board);
         displaypositions(parts);
         delay(100);
         turnOffDisplay();
         delay(100);
         sq_dest = scanPieceArray(&board);

        //If the piece goes back to its original square...
         if(sq_dest == sq_source)
         {
            //TODO: check if empty return is safe.
            return;
         }

    }

     //TODO: convert fen to an Arduino String
     // Send FEN to boardcaster.com
    char* fen_char = chess.getFENFromPosition();
    String fen_string = String(fen_char);
     /*setNextFEN(fen_string);*/
     /*sendData();*/

    Serial.print("FEN: "); Serial.println(fen_string);

}
