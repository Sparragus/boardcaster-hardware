#ifndef LED_DISP_H
#define LED_DISP_H

#include <WProgram.h>

void initLedDisp();
void displayIllegalPos(int pos);
uint16_t *getParts(uint64_t* board);
void shiftOut16(uint8_t LA_DATA_PIN, uint8_t clockPin, uint8_t bitOrder, uint16_t val);
void displayPositions(uint16_t* positions);
void lockDisplay();
void clearDisplay();
#endif //LED_DISP_H

