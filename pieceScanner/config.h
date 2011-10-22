
// MUX = Columns
// DECs = ROWS
#define MUX_PA 7
#define MUX_PB 6
#define MUX_PC 5
	
#define DEC_PA 4
#define DEC_PB 3
#define DEC_PC 2
		
#define OUT_DATA 8
#define SCAN_SIZE 64
const long unsigned TIME_SETTLE = 0;
const long unsigned TIME_NEXT = 1;

// Hold all the states
typedef unsigned int uint;
typedef unsigned char uchar;

struct sig_t {
  uchar m_port1;
  uchar m_port2;
  uchar m_port3;

} sig;
