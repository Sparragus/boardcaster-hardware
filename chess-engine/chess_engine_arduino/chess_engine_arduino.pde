#include "position.h"
#include "fen.h"
#include "diag.h"

void setup() {
  // put your setup code here, to run once:

    char start_pos[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    position pos;

    loadPositionFromFEN(start_pos, &pos);
    printPosition(&pos);
}

void loop() {
  // put your main code here, to run repeatedly:

}
