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

  Serial.begin(9600);
  
}


void displayIllegalPos(int pos)
{
  uint64_t xn; 
  
}

/* // Get bit from board */
uint16_t *getParts(uint64_t* board)
{

  static uint16_t board_parts[4];
  board_parts[0] = *board;
  board_parts[1] = (*board >> 16);
  board_parts[2] = (*board >> 32);
  board_parts[3] = (*board >> 48);

  return board_parts;
}

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

void displaypossisions(uint16_t* possisions)
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
  for(int i = 0; i < 4; i++)
    {
  shiftOut16(dataPin, clockPin, MSBFIRST, possisions[4-i]);
    }

        
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

  uint64_t bitboard = 0xFFFF000FFFFF000F;
  uint16_t  *x = getParts(&bitboard);

  for(int i = 0; i < 4; i++)
    {
      Serial.println(x[i], BIN);
    }
  Serial.println("blah");
  

  displaypossisions(x);
  
  delay(500);
}

