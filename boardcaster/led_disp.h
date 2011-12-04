#ifndef LED_DISP_H
#define LED_DISP_H

#include <WProgram.h>

void initLedDisp();
void shiftOut16(uint8_t LA_DATA_PIN, uint8_t clockPin, uint8_t bitOrder, uint16_t val);
void displayPositions(const uint64_t* inBoard);
void lockDisplay();
void clearDisplay();
#endif //LED_DISP_H

