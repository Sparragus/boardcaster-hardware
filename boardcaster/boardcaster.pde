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
#include "utils.h"

#include "MemoryFree.h"

#include <stdlib.h>
#include <avr/pgmspace.h>

#define NDEBUG
// Just in case.
#define assert(x) ;

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
uint64_t board = 0x0ULL;

// Main firmware setup call
void setup()
{
    delay(1000);
    Serial.end();
    // Set serial transmission rate for debug prints
    Serial.begin(9600);
    delay(1000);
    showString(PSTR(""));
    showBanner();
    showString(PSTR("\n"));
    showString(PSTR("\nInitializing Piece Detector..."));
    
    // Initialize the piece detector
    initPieceDetector();
    showString(PSTR("done\n"));

    showString(PSTR("Initializing LED Array..."));
    // Initialize the LED array
    initLedDisp();
    showString(PSTR("done\n"));

    showString(PSTR("Cycling LED Array..."));
    // Run LED diagnostics
    //  cycleArray();
    clearDisplay();

    showString(PSTR("done\n"));

    // Init web posting code
    //initPoster();

    // Init chess engine
    //chess = Chess("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    // chess = Chess("8/8/8/8/4Q3/8/8/k3K3 w KQkq - 0 1");
    chess = Chess("3k3r/8/8/8/8/8/1K6/RNBP4 w KQkq - 0 1");

    showString(PSTR("Expected starting board\n\n"));

    chess.printOwnPosition();

    showString(PSTR("Getting board state"));

    // Scan the board a few times first
   
    scanPieceArray(&board);
    showString(PSTR("\nReady\n\n"));
    showString(PSTR("MEM: "));
    Serial.println(freeMemory(), DEC);
    
}

// Main firmware loop
void loop()
{
    showString(PSTR("START---ITERATION----------------------------------------------\n"));
    // Get current position
   
    board  = chess.getCurrentPosition();

    showString(PSTR("CurrentPosition=\n"));
    chess.printBitboard(&board);
     
    // ---------------------------------------
    // LIFT PIECE
    //
    //

    scanPieceArray(&board);
    
    // Scan piece array until a change is detected
    // sq >= 0 if Board changed; Square that changed, sq = -1 = No change
    int sq_source = -1;
     do
    {
        showString(PSTR("^ "));
        sq_source = scanPieceArray(&board);
       
    }
    while(sq_source == -1 || 63-sq_source==27);
  
    showString(PSTR("\n"));
    // sq_source = emulate_board(&board, 0);

    sq_source = 63 - sq_source;
    showString(PSTR("Found lifted piece: ")); Serial.println(sq_source, DEC);
    showString(PSTR("Current board\n"));
    // chess.printBitboard(&board); 
   //printBoard(&board,64);
    // Obtain a bitboard with the legal moves for a piece on the square sq
    const uint64_t moves = chess.getPieceMoves( sq_source );
    
    //   showString(PSTR("Found the following moves\n"));
//    chess.printBitboard(&moves);


    showString(PSTR("preDisplayPositions -> MEM: "));
    Serial.println(freeMemory(), DEC);
 
     displayPositions(&moves);  

     showString(PSTR("postDisplayPositions -> MEM: "));
    Serial.println(freeMemory(), DEC);

   
    //
    //
    // ---------------------------------------------------








    // --------------------------------------------------
    // SET PIECE
    //
    //

    // Scan piece array until a change is detected
    // sq_source >= 0 if Board changed; Square that changed, sq_source = -1 = No change
    int sq_dest = -1;
    do
    {
  
        // showString(PSTR("v "));
        sq_dest = scanPieceArray(&board);
 
 
    }
    while(sq_dest == -1 || 63-sq_dest==27);
    showString(PSTR("\n"));
    
   // sq_dest = emulate_board(&board, 1);
    sq_dest = 63 - sq_dest;
    showString(PSTR("Found placed piece: ")); Serial.println(sq_dest, DEC);
    clearDisplay();
   

    // Piece is placed, turn off leds
  
    // If sq_source == sq_dest, then piece was placed back to it's original pos
    // Don't play the move. Loop again.
    if(sq_source == sq_dest)
    {
        //TODO: check if empty return is safe.
        clearDisplay();
        showString(PSTR("Set piece at same position!\n"));
        showString(PSTR("END---ITERATION----------------------------------------------\n"));
        return;
    }
    chess.playPieceMove(sq_dest);

    showString(PSTR("chess.playPieceMove -> MEM: "));
    Serial.println(freeMemory(), DEC);

    // TODO: Confirn correct code logic
/*
    uint64_t error_board = 0x0ULL;
    // legal == 0 if move is legal, else legal == 1, meaning move is illegal
    // while move is illegal...
    while(chess.playPieceMove(sq_dest) != 0)
    {
        if( sq_dest >= 0 )
        {
            showString(PSTR("Error board!\n"));
            error_board = chess.getMask(sq_dest);
        }
        uint16_t* parts  = getParts(&error_board);
        displayPositions(parts);
        delay(500);
        clearDisplay();
        // HACK
        sq_dest = scanPieceArray(&board);
        printBoard(&board, 64);
     
        sq_dest = 63 - sq_dest;

        //If the piece goes back to its original square...
        if(sq_dest == sq_source)
        {
            //TODO: check if empty return is safe.
            //return;
        }
        showString(PSTR("Waiting for a valid move\n"));
    }
*/

    // -------------------------------------------------
    


    //TODO: convert fen to an Arduino String
    // Send FEN to boardcaster.com
    showString(PSTR("Getting FEN from position\n"));
    char* fen_char = chess.getFENFromPosition();
    showString(PSTR("Got FEN from position\n"));
    String fen_string = String(fen_char);
    showString(PSTR("Posting FEN\n"));
    //     setNextFEN(fen_string);
    //     sendData();

    showString(PSTR("FEN: ")); Serial.println(fen_string);
    showString(PSTR("END---ITERATION----------------------------------------------\n"));

}

