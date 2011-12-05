#ifndef _DEFINES_H
#define _DEFINES_H

// Pin Definitions
// ------------

// LED Array
//Pin connected to S-IN of IR2D07s
#define LA_DATA_PIN A0
//Pin connected to CLK of IR2D07s
#define LA_CLOCK_PIN A1
//Pin connected to LATCH of IR2D07s
#define LA_LATCH_PIN A2
//Pin connected to XEN of IR2D07s
#define LA_XEN_PIN A3

// Piece detector

// MUX = Columns
// DECs = ROWS
#define PD_MUX_PA 36  // LSB //
#define PD_MUX_PB 34         //
#define PD_MUX_PC 32 // MSB  //
	
#define PD_DEC_PA0 42 // LSB //
#define PD_DEC_PA1 40       //
#define PD_DEC_PA2 38 // MSB //
		
#define PD_OUT_DATA 30


#endif // _DEFINES_H


