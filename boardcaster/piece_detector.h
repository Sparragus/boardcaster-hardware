#ifndef PIECE_DETECTOR_H
#define PIECE_DETECTOR_H
// Pin Definitions

// MUX = Columns
// DECs = ROWS
#define MUX_PA 7  // MSB // C - Pin9
#define MUX_PB 6         // B - Pin10
#define MUX_PC 5 // LSB  // A - Pin11
	
#define DEC_PA0 4 // MSB // A2 - Pin3
#define DEC_PA1 3        // A1 - Pin2
#define DEC_PA2 2 // LSB // A0 - Pin1
		
#define OUT_DATA 8

// Under non-debugging operation SENSOR_COUNT = SCAN_SIZE = 64
#define SCAN_SIZE 64
#define SENSOR_COUNT 64

#define PRINT_RES 0
#define PRINT_TIME 0
//#define DEBUG
typedef unsigned long long uint64_t;
// Temporary board for delta calculation
extern uint64_t old_board;

// Time in ms to wait until reading the data
// units in ms.
// 1ms SETTLE ~~ 64ms per board scan
// 5ms SETTLE ~~ 322ms per board scan
extern const long unsigned TIME_SETTLE;
extern long unsigned realTimeToScan;

// Hold all the states
typedef unsigned int uint;
typedef unsigned char uchar;

extern struct sig_t {
  uchar m_port1;
  uchar m_port2;
  uchar m_port3;

} sig;

int scanPieceArray(uint64_t* board);
void initPieceDetector();

#endif //PIECE_DETECTOR_H
