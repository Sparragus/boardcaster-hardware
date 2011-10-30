//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a IR2D07 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

//Pin connected to S-IN of IR2D07
int dataPin = 8;
//Pin connected to CLK of IR2D07
int clockPin = 9;
//Pin connected to LATCH of IR2D07
int latchPin = 10;
//Pin connected to XEN of IR2D07
int xenPin = 11;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(xenPin, OUTPUT);
  
  digitalWrite(latchPin, HIGH);
}

void loop() {

    // take the xenPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(xenPin, LOW);
    
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, 255);  

    //take the xen pin high so the LEDs will light up:
    digitalWrite(xenPin, HIGH);
    // pause before next value:
    delay(1000);
    
    digitalWrite(xenPin, LOW);
    
    delay(1000);

}
