#ifndef LED_DISP_H
#define LED_DISP_H
// Pin Definitions

//Pin connected to S-IN of IR2D07s
#define dataPin = 2;
//Pin connected to CLK of IR2D07s
#define clockPin = 3;
//Pin connected to LATCH of IR2D07s
#define latchPin = 4;
#define latchPin2 = 6;
//Pin connected to XEN of IR2D07s
#define xenPin = 5;
#define xenPin2 = 7;

void initLedDisp();
void displayIllegalPos(int pos);
uint16_t *getParts(uint64_t* board);
void shiftOut16(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint16_t val);
void displaypossisions(uint16_t* possisions);

#endif //LED_DISP_H
