#ifndef PIECE_DETECTOR_H
#define PIECE_DETECTOR_H
// Pin Definitions
#include <stdlib.h> 


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
