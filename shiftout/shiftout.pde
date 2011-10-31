// Code by Gabriel J. Perez
//         Francisco De La Cruz

//Pin connected to S-IN of IR2D07
int dataPin = 2;
//Pin connected to CLK of IR2D07
int clockPin = 3;
//Pin connected to LATCH of IR2D07
int latchPin = 4;
//Pin connected to XEN of IR2D07
int xenPin = 5;

int latchPin2 = 6;
int xenPin2 = 7;

unsigned int j = 2;
const int disp[] = { 0, 0, 0, 0};
const int disp2[] = { 0, 0, 0, 1};

void setup() {
  //set pins to output so you can control the shift register
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  pinMode(xenPin, OUTPUT);
  pinMode(xenPin2, OUTPUT);
  
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin2, HIGH);
  
}


void displayIllegalPos(int pos)
{
  uint64_t x; 
  
}

/* // Get bit from board */
/* int getBit(uint64_t* board) */
/* { */

/*   unsigned int res = 0L; */
/*   uint64_t hi  = (*board >> 16) & 0x00000000FFFFFFFFULL; */
/*   uint64_t lo =  *board & 0x00000000FFFFFFFFULL; */
  
/*   if(bit < 31) */
/*     res = (hi >> (31-bit)) & 1L; */
/*   else */
/*     { */
/*       bit -=32; */
/*       res = (lo >> (31-bit)) & 1L; */
/*     } */
/*   return res; */
/* } */

void shiftOut16(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint16_t val)
{
  uint16_t i;

  for (i = 0; i < 16; i++) {
    if (bitOrder == LSBFIRST)
      digitalWrite(dataPin, !!(val & (1 << i)));
    else
      digitalWrite(dataPin, !!(val & (1 << (16 - i))));

    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }
}

void displaydata(int shift1, int shift2)
{
  // Set xenPin high to disable the drivers.
  // Set the latch low to allow data through latch. This might
  // have to be revised.
  digitalWrite(xenPin, HIGH);
  digitalWrite(xenPin2, HIGH);
  digitalWrite(latchPin, LOW);
  digitalWrite(latchPin2, LOW);
  // Set the clockPin low to prepare for rising edge trigger
  digitalWrite(clockPin, LOW);  
  // Shift out the data
  int x = 255;
  shiftOut16(dataPin, clockPin, MSBFIRST, shift1);
  shiftOut16(dataPin, clockPin, MSBFIRST, shift2);  
        
  // Set latch high to capture latch
  // Set xenPin low to enable the drivers
  // Set latchPin low to allow data to pass through
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin2, HIGH);
  digitalWrite(xenPin, LOW);
  digitalWrite(xenPin2, LOW);
  digitalWrite(latchPin, LOW);
  digitalWrite(latchPin2, LOW);

  // Delay about 1sec per number    
  delay(100);

}

void loop() {
   
  displaydata(65535, 0);
     
}

