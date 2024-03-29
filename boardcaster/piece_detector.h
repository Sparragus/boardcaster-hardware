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


typedef unsigned long long uint64_t;

// Temporary board for delta calculation
extern uint64_t old_board;


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

