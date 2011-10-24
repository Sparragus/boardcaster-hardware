
// MUX = Columns
// DECs = ROWS
#define MUX_PA 7
#define MUX_PB 6
#define MUX_PC 5
	
#define DEC_PA0 4
#define DEC_PA1 3
#define DEC_PA2 2
		
#define OUT_DATA 8
#define SCAN_SIZE 64
// Time in ms to wait until reading the data
// units in ms.
// 1ms SETTLE ~~ 64ms per board scan
const long unsigned TIME_SETTLE = 1;


// Hold all the states
typedef unsigned int uint;
typedef unsigned char uchar;

struct sig_t {
  uchar m_port1;
  uchar m_port2;
  uchar m_port3;

} sig;
