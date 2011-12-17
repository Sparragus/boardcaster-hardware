/*Copyright (C) 2011  Francisco De La Cruz, Gabriel J. Pérez
  and Richard B. Kaufman

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef _DEFINES_H
#define _DEFINES_H

// Pin Definitions
// ------------

// LED Array
// ---------
//Pin connected to S-IN of IR2D07s
#define LA_DATA_PIN A0
//Pin connected to CLK of IR2D07s
#define LA_CLOCK_PIN A1
//Pin connected to LATCH of IR2D07s
#define LA_LATCH_PIN A2
//Pin connected to XEN of IR2D07s
#define LA_XEN_PIN A3

// Piece detector
// -----------
// MUX = Columns
// DECs = ROWS
#define PD_MUX_PA 36  // LSB //
#define PD_MUX_PB 34         //
#define PD_MUX_PC 32 // MSB  //
	
#define PD_DEC_PA0 42 // LSB //
#define PD_DEC_PA1 40       //
#define PD_DEC_PA2 38 // MSB //
		
// PCB Out = Arduino IN
#define PD_OUT_DATA 30


#endif // _DEFINES_H


