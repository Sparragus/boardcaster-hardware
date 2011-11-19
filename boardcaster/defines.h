#ifndef _DEFINES_H
#define _DEFINES_H

// Pin Definitions
// ------------

// LED Array
//Pin connected to S-IN of IR2D07s
#define LA_DATA_PIN 2
//Pin connected to CLK of IR2D07s
#define LA_CLOCK_PIN 3
//Pin connected to LATCH of IR2D07s
#define LA_LATCH_PIN 4
#define LA_LATCH_PIN2 6
//Pin connected to XEN of IR2D07s
#define LA_XEN_PIN 5
#define LA_XEN_PIN2 7

// Piece detector

// MUX = Columns
// DECs = ROWS
#define PD_MUX_PA 5  // MSB // C - Pin9
#define PD_MUX_PB 6         // B - Pin10
#define PD_MUX_PC 7 // LSB  // A - Pin11
	
#define PD_DEC_PA0 4 // MSB // A2 - Pin3
#define PD_DEC_PA1 3        // A1 - Pin2
#define PD_DEC_PA2 2 // LSB // A0 - Pin1
		
#define PD_OUT_DATA 8


#endif // _DEFINES_H

