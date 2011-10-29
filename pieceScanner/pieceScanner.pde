
#include "config.h"
#include "utils.h"
#include "hw_signals.h"
#include "bit_ops.h"
#include "bitboard_ops.h"


void initPieceDetector();

// Main firmware setup call
void setup()
{
 
    // Set serial transmission rate for debug prints
    Serial.begin(9600);
  
    // Initialize the piece detector
    initPieceDetector();
  
}

// Piece Detector Initializer
void initPieceDetector()
{

    Serial.print("Initializing Piece Array Scanner");	

    // Set up pin directions
    pinMode(DEC_PA0, OUTPUT);
    pinMode(DEC_PA1, OUTPUT);
    pinMode(DEC_PA2, OUTPUT);
    pinMode(MUX_PA, OUTPUT);
    pinMode(MUX_PB, OUTPUT);
    pinMode(MUX_PC, OUTPUT);

    // Set output pin
    pinMode(OUT_DATA, INPUT);

    // Disable internal pullup
    digitalWrite(OUT_DATA, LOW);

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
    Serial.println("\nInitialization Done.");	
  

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
    if(tboard[0] != getBit(board,0) && tboard[1] != getBit(board,1))
        Serial.print("getBitFailure");
  
#if PRINT_RES == 1
    Serial.print("NEW BOARD ");
    printBoard(board,  SENSOR_COUNT);
    Serial.print("OLD BOARD ");
    printBoard(&old_board,  SENSOR_COUNT);
    Serial.print("Full compare: ");
    Serial.print(old_board == *board, BIN);
    Serial.println("");
#endif
    return compareBoards(board, &old_board, SENSOR_COUNT);

}

// Compare board1 against board2 for the specified amount of sensors
// Under normal operation SENSOR_COUNT = SCAN_SIZE
// Return: 0 = Equal boards
// Return: 1 = Different boards;
int compareBoards(uint64_t* board1, uint64_t* board2, const int sensorCount)
{
    for(int i = 0; i < sensorCount; i++)
        if(getBit(board1,i) != getBit(board2,i))
            return 1;
    return 0;
}

// Prints a bitboard up to n positions
void printBoard(uint64_t* board, int n)
{
    Serial.print("[");
    for(int i = 0; i < n && i < SCAN_SIZE; i++)
    {
        if(n > 8 && i%8 == 0)
            Serial.println("");
        Serial.print(getBit(board,i), DEC);
        if(i+1 != n && i != SCAN_SIZE)
            Serial.print(", ");
    }
    Serial.println("]");
}

// Convert array of board into a bitboard
void arrayToBitBoard(uchar* array, uint64_t* board)
{
    uint64_t temp = 0LL;
  
    for(int i = 0; i < SCAN_SIZE; i++)
    {
        if(array[63-i] == 1)
        {
            temp |= 1LL<<i; 
        }
    }
    *board = temp;
}


// Get bit from board
uchar getBit(uint64_t* board, uchar bit)
{
    unsigned long int res = 0L;
    uint64_t hi  = (*board >> 32) & 0x00000000FFFFFFFFULL;
    uint64_t lo =  *board & 0x00000000FFFFFFFFULL;
  
    if(bit < 31)
        res = (hi >> (31-bit)) & 1L;
    else
    {
        bit -=32;
        res = (lo >> (31-bit)) & 1L;
    }
    return res;
}

// Set bit to data of board.
void putBit(uint64_t* board, uchar data, uchar bit)
{
  
    uint64_t board_hi = (*board >> 32)  & 0x00000000FFFFFFFFULL;
    uint64_t  board_lo = *board & 0x00000000FFFFFFFFULL;

    if(data == 0)
    {
        if(bit >= 0 && bit < 32)
        {
            board_hi = board_hi &  ~(1L<<(31-bit));
        }
        else if(bit >=32 && bit < 64)
        {
            bit -= 32;
            board_lo &= ~(1L<<(31-bit));
        }
    }
    else if (data == 1)
    {
        if(bit >= 0 && bit < 32)
        {
            board_hi = board_hi | (1L<<(31-bit));
        }
        else if(bit >=32 && bit < 64)
        {
            bit -= 32;
            board_lo |= (1L<<(31-bit));
        } 
    }
  
    *board  = board_lo | (board_hi << 32);

    // Assert the bits. This should NEVER assert false
    if (getBit(board, bit) != data)
    {
#ifdef DEBUG
        Serial.print("Got: ");
        Serial.print(getBit(board, bit), BIN);
        Serial.print(" Expected: ");
        Serial.print(data, BIN);
        Serial.println(" Assert setting bit!");
#endif
    }
}

// Get result from the piece array
int readPieceArrayLine()
{
    return digitalRead(OUT_DATA);
}

// Set decoder to the given signal
void setDecoder(sig_t* s)
{
    // 74HCT138 Decoder uses reversed select pins as well
    // Output = Input
    // Yx =   C B A
    // ~Y0 =  0 0 0
    // ~Y1 =  0 0 1
#ifdef DEBUG
    Serial.print("DEC: ");
    Serial.print(s->m_port1,DEC);
    Serial.print(",");
    Serial.print(s->m_port2,DEC);
    Serial.print(",");
    Serial.println(s->m_port3,DEC);
#endif
    digitalWrite(DEC_PA0, s->m_port1);
    digitalWrite(DEC_PA1, s->m_port2);
    digitalWrite(DEC_PA2, s->m_port3);
}

// Set Multiplexer to the given signal
void setMux(sig_t* s)
{ 
    // MAX4581 Multiplexer uses reversed select pins
    // MSB is C LSB is A
    // X0 - 0 0 0 ( C B A)
    // X1 - 0 0 1 ( C B A)

    // Please wire accordingly. 

    /*
      |o   |
      |    |
      |    |
      |    |A
      |    |B
      |____|C

    */

#ifdef DEBUG
    Serial.print("MUX: ");
    Serial.print(s->m_port1,DEC);
    Serial.print(",");
    Serial.print(s->m_port2,DEC);
    Serial.print(",");
    Serial.println(s->m_port3,DEC);
#endif
    digitalWrite(MUX_PA, s->m_port1);
    digitalWrite(MUX_PB, s->m_port2);
    digitalWrite(MUX_PC, s->m_port3);
}

// Generate signal s from decimal input i
void generateSig(uchar i, sig_t* s)
{
    uchar a = (i&0x4)>>2;
    uchar b = (i&0x2)>>1;
    uchar c = i&0x1;

    s->m_port1 = a;
    s->m_port2 = b;
    s->m_port3 = c;
}

// Convert linear position to 2D position
void linTo2D(uchar i, uchar* x, uchar* y)
{
    uchar yt = i/8;
    uchar xt = i%8;

    *x = xt;
    *y = yt;
}

