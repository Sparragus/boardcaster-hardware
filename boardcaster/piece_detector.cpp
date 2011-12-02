#include <WProgram.h>
#include "piece_detector.h"
#include "utils.h"
#include "hw_signals.h"
#include "bitboard_ops.h"
#include "defines.h"
#include "led_disp.h"

#define PRINT_RES 0

uint64_t old_board = 0x0000000000000000LL;
const long unsigned  TIME_SETTLE = 1;
long unsigned realTimeToScan = 0;

void cycleArray()
{
    uint64_t board = 0x0000000000000000LL;
    uint16_t* parts = 0LL; 
    int dir = 1;

    int bitPos = 0;
    int p =0;

    for(int j = 0; j < 8; j++)
    {
        bitPos = p;
        for(int i = 0; i < 8; i++)

        { 
            putBit(&board, 1, bitPos);
            parts  = getParts(&board);
            delay(30);
            displaypositions(parts);
            delay(50);
            bitPos += dir;
        }
     
        dir = -dir;
        if(j%2==0)
            p+=15;
        else
            p+=1;
    } 


}



// Scan the board into the long long board (64 bits)
// Return: 1 = Board Change
//       : 0 = No Board Change
int scanPieceArray(uint64_t* board)
{
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
        // As connected DEMO

        // Enable Decoder
        setDecoder(&row);

        // Enable Multiplexer
        setMux(&col);

        // Wait for settle
        delay(TIME_SETTLE);
    
        // Read Result
        uchar data = readPieceArrayLine();
        tboard[i] = data;
    }
 
    // Save old board
    old_board = *board;
 
    // Convert array bit board into a long long 
    arrayToBitBoard(tboard, board);
 
    // Assert conversion failure
    // This should NEVER happen.
    if(tboard[0] != getBit(board, 0) && tboard[1] != getBit(board, 1))
        Serial.print("getBitFailure");
  
#if PRINT_RES == 1
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

// Piece Detector Initializer
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


