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
#define PD_MUX_PA 5  // LSB //
#define PD_MUX_PB 6         //
#define PD_MUX_PC 7 // MSB  //
	
#define PD_DEC_PA0 2 // LSB //
#define PD_DEC_PA1 3        //
#define PD_DEC_PA2 4 // MSB //
		
#define PD_OUT_DATA 8


#endif // _DEFINES_H


