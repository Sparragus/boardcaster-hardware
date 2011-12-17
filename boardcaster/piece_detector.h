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

#ifndef PIECE_DETECTOR_H
#define PIECE_DETECTOR_H

#include <stdlib.h> 

// Under non-debugging operation SENSOR_COUNT = SCAN_SIZE = 64
#define SCAN_SIZE 64
#define SENSOR_COUNT 64

#define PRINT_RES 0
#define PRINT_TIME 0

// Disable debug output to Serial.
//#define DEBUG

typedef unsigned long long uint64_t;

// Temporary board for delta calculation
extern uint64_t old_board;

// Time in ms to wait until reading the data
// units in ms.
// 1ms SETTLE ~~ 64ms per board scan
// 5ms SETTLE ~~ 322ms per board scan
// Definition in piece_detector.cpp
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
void cycleArray();

#endif //PIECE_DETECTOR_H

