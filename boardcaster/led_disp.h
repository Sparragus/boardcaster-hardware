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

#ifndef LED_DISP_H
#define LED_DISP_H

#include <WProgram.h>

void initLedDisp();
void shiftOut16(uint8_t LA_DATA_PIN, uint8_t clockPin, uint8_t bitOrder, uint16_t val);
void displayPositions(const uint64_t* inBoard);
void lockDisplay();
void clearDisplay();
void flashOK();
#endif //LED_DISP_H

