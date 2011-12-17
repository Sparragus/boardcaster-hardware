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

#ifndef CONFIG_H
#define CONFIG_H

// Define to allow calls to showString(...) to print to Serial
#define ENABLE_SHOWSTRING

// Always leave this defined to remove asserts
#define NDEBUG
// Just remove the asserts
#define assert(x) ;

// Uncomment to print debug messages
//#define DEBUG

// Time in ms to wait until reading the data
// units in ms.
// 1ms SETTLE ~~ 64ms per board scan
// 5ms SETTLE ~~ 322ms per board scan

// Just settle for 1ms
#define TIME_SETTLE 1


// Under non-debugging operation SENSOR_COUNT = SCAN_SIZE = 64
#define SCAN_SIZE 64
#define SENSOR_COUNT 64

#define PRINT_RES 0
#define PRINT_TIME 0

// Define for a board mirrored along the file axis
#define MIRRORED_FILES


#endif // CONFIG_H
