
// Pin Definitions

// MUX = Columns
// DECs = ROWS
#define MUX_PA 7
#define MUX_PB 6
#define MUX_PC 5
	
#define DEC_PA0 4
#define DEC_PA1 3
#define DEC_PA2 2
		
#define OUT_DATA 8


// Under non-debugging operation SENSOR_COUNT = SCAN_SIZE = 64
#define SCAN_SIZE 64
#define SENSOR_COUNT 6


#define PRINT_RES 0
#define PRINT_TIME 0

// Temporary board for delta calculation
uint64_t old_board = 0x0000000000000000LL;


// Time in ms to wait until reading the data
// units in ms.
// 1ms SETTLE ~~ 64ms per board scan
// 5ms SETTLE ~~ 322ms per board scan
const long unsigned TIME_SETTLE = 5;

long unsigned realTimeToScan = 0;

// Hold all the states
typedef unsigned int uint;
typedef unsigned char uchar;

struct sig_t {
  uchar m_port1;
  uchar m_port2;
  uchar m_port3;

} sig;
