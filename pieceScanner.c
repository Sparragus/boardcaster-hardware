#include <iostream>
#include <stdio.h>
#include <unistd.h>



#define WIDTH 8
#define HEIGHT 8

#define ARDUINO 0
// MUX = Columns
// DECs = ROWS
#define MUX_PA 7
#define MUX_PB 6
#define MUX_PC 5
	
#define DEC_PA 4
#define DEC_PB 3
#define DEC_PC 2
		
#define OUT_DATA 8

#define TIME_SETTLE 200
#define TIME_NEXT  10

#define OUT_DATA 0

// Hold all the states
typedef unsigned int uint;
typedef unsigned char uchar;

struct sig
{
    uchar PORT1;
    uchar PORT2;
    uchar PORT3;
};

void scanPieceArray();
void generateSig(uchar c, sig *s);
int readPieceArrayLine();
void linTo2D(uchar i, uchar* x, uchar* y);
void delay(uint ms);
void setDecoder(sig *s);
void setMux(sig *s);

#if ARDUINO == 0

#define HIGH 1
#define LOW 0
#define INPUT 0

void pinMode(int pin, int mode)
{
	// No one here but us chickens...
}

void digitalWrite(int pin, int data)
{
	// No one here but us chickens...
}

int digitalRead(int pin)
{
	// No one here but us chickens...
}

#endif

void setup()
{
    // Set up pin directions
    pinMode(DEC_PA, OUT);
    pinMode(DEC_PB, OUT);
    pinMode(DEC_PC, OUT);
    pinMode(MUX_PA, OUT);
    pinMode(MUX_PB, OUT);
    pinMode(MUX_PC, OUT);

    pinMode(OUT_DATA, INPUT);

	 // Disable internal pullup
	digitalWrite(OUT_DATA, LOW);
	
	// Set serial transmission rate for debug prints
	Serial.begin(9600);
	
}


int main()
{
	while(;)
	{
		// Scan piece array
		uchar board[64];
		scanPieceArray(board);	
	}
	// Run the chess engine step
	
    return 0;
}

void scanPieceArray(uchar* board)
{

#if ARDUINO == 0
		printf("Initializing Piece Array Scanner\n");
#elif
		Serial.println("Initializing Piece Array Scanner");
#endif
		uchar x, y = 0;
		
		//Scan the board
		// Run i from 0 to 63
	for(unsigned int i = 0; i < 64; i++)
	{
	
	  linTo2D(i, &x, &y);
#if ARDUINO == 0
	   printf("Moving .. %d %d \n", x, y);
#elif
		Serial.print("Moving .. ");
		Serial.print(x);
		Serial.print(",");
		Serial.println(y);
#endif

        sig col, row;

        generateSig(x, &col);
        generateSig(y, &row);

        // Enable Decoder
        setDecoder(&col);


        // Enable Multiplexer
        setMux(&row);

        // Wait for settle
        delay(TIME_SETTLE);

        // Read Result
        uchar data = readPieceArrayLine();

        // Save the result
        board[i] = data;


        // Wait for next
        delay(TIME_NEXT);
    }
}
int readPieceArrayLine()
{
    return digitalRead(OUT_DATA);
}

void setDecoder(sig *s)
{
    digitalWrite(DEC_PA, s->PORT1);
    digitalWrite(DEC_PB, s->PORT2);
    digitalWrite(DEC_PC, s->PORT3);
}

void setMux(sig *s)
{
    digitalWrite(MUX_PA, s->PORT1);
    digitalWrite(MUX_PB, s->PORT2);
    digitalWrite(MUX_PC, s->PORT3);
}

void generateSig(uchar i, sig *s)
{
    uchar a = (i&0x4)>>2;
    uchar b = (i&0x2)>>1;
    uchar c = i&0x1;


    //  printf("%d to bin %d %d %d\n", i, a, b, c);
    s->PORT1 = a;
    s->PORT2 = b;
    s->PORT3 = c;
}

void linTo2D(uchar i, uchar* x, uchar* y)
{
    uchar yt = i/8;
    float xt = i%8;

    *x = xt;
    *y = yt;
}

void delay(uint ms)
{
    usleep(ms*1000);
}
