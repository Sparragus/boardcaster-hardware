#include <WProgram.h>
#include "piece_detector.h"
#include "led_disp.h"
#include "utils.h"


void setup()
{
	Serial.begin(9600);
	Serial.println("Starting cycler...");
	initPieceDetector();
	initLedDisp();
	
       	cycleArray();
	delay(500);
	clearDisplay();
} 
uint64_t board = 0x00ULL;
void loop()
{    
	
	scanPieceArray(&board);
	displayPositions(&board);
	Serial.println(".");
	delay(10);

}
