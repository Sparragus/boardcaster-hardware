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

#include <WProgram.h>
#include "piece_detector.h"
#include "defines.h"

// Get result from the piece array
int readPieceArrayLine()
{
    return digitalRead(PD_OUT_DATA);
}

// Set decoder to the given signal structure
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
    // Remember to swap the MSB and LSB
    digitalWrite(PD_DEC_PA2, s->m_port1);
    digitalWrite(PD_DEC_PA1, s->m_port2);
    digitalWrite(PD_DEC_PA0, s->m_port3);
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

// Is the board mirrored along the file axis
#ifdef MIRRORED_FILES
    s->m_port1 = (uchar)(!(s->m_port1));
    s->m_port2 = (uchar)(!(s->m_port2));
    s->m_port3 = (uchar)(!(s->m_port3));
#endif

#ifdef DEBUG
    Serial.print("MUX: ");
    Serial.print(s->m_port1,DEC);
    Serial.print(",");
    Serial.print(s->m_port2,DEC);
    Serial.print(",");
    Serial.println(s->m_port3,DEC);
#endif
    
    digitalWrite(PD_MUX_PC, s->m_port1);
    digitalWrite(PD_MUX_PB, s->m_port2);
    digitalWrite(PD_MUX_PA, s->m_port3);
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

