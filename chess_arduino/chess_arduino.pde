#include <bitboard.h>
#include <position.h>
#include <move.h>
#include <fen.h>
#include <attack.h>
#include <Chess.h>

/*
This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

 @Author: Richard B. Kaufman-Lopez <richardbkaufman [at] gmail [dot] com>
 */



void setup()
{
    Serial.begin(9600);

    Serial.println("Setup...");

    Chess chess("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    Serial.println("Constructed chess...");

    bitboard playableBitboard = 0;
    playableBitboard = chess.getPieceMoves(1);
    Serial.println("Got moves...");
    chess.printBitboard(&playableBitboard);

    Serial.println("Printed moves...");
}

void loop()
{


}

