#ifndef LED_DISP_H
#define LED_DISP_H

void initLedDisp();
void displayIllegalPos(int pos);
uint16_t *getParts(uint64_t* board);
void shiftOut16(uint8_t LA_DATA_PIN, uint8_t clockPin, uint8_t bitOrder, uint16_t val);
void displaypossisions(uint16_t* possisions);

#endif //LED_DISP_H
