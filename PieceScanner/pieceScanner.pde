#include <iostream>
#include <stdio.h>
#include <unistd.h>

// Hold all the states
unsigned char board[64];
typedef unsigned int uint;
typedef unsigned char uchar;


struct sig
{
    uchar PORT1;
    uchar PORT2;
    uchar PORT3;
};
int readPieceArrayLine();
void linTo2D(uchar i, uchar* x, uchar* y);
void delay(uint ms);
void setDecoder(sig *s);
void setMux(sig *s);

#define WIDTH 8
#define HEIGHT 8

#define ARDUINO 0

#define MUX_PA 0
#define MUX_PB 0
#define MUX_PC 0

#define DEC_PA 0
#define DEC_PB 0
#define DEC_PC 0

#define OUT 0

#define TIME_SETTLE 200
#define TIME_NEXT  10

#if ARDUINO == 0
#define HIGH 1
#define LOW 0
#define IN 0
#define OUT_DATA 0

void pinMode(int pin, int mode)
{


}

void digitalWrite(int pin, int data)
{

}

int digitalRead(int pin)
{

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

    pinMode(OUT_DATA, IN);

}

void generateSig(uchar c, sig *s);
int main()
{
    printf( "OK\n");
    unsigned char x, y = 0;
    // Run i from 0 to 63
    printf( "OK\n");
    for(unsigned int i = 0; i < 64; i++)
    {

        linTo2D(i, &x, &y);
#if ARDUINO == 0
        printf("Moving .. %d %d \n", x, y);
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
    return 0;
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
