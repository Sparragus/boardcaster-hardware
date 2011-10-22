
#include "config.h"
void scanPieceArray(uint64_t* board);
void linTo2D(uchar i, uchar* x, uchar* y);
void generateSig(uchar i, sig_t* s);
void setDecoder(sig_t* s);
void setMux(sig_t* s);
int readPieceArrayLine();
void setBit(uint64_t* board, uchar data, uchar bit);
uchar getBit(uint64_t* board, uchar bit);
void arrayToBitBoard(uchar* array, uint64_t* board);
uchar tboard[SCAN_SIZE];

void setup()
{
  // Set up pin directions
  pinMode(DEC_PA, OUTPUT);
  pinMode(DEC_PB, OUTPUT);
  pinMode(DEC_PC, OUTPUT);
  pinMode(MUX_PA, OUTPUT);
  pinMode(MUX_PB, OUTPUT);
  pinMode(MUX_PC, OUTPUT);

  pinMode(OUT_DATA, INPUT);


  // Disable internal pullup
  digitalWrite(OUT_DATA, LOW);
	
  // Set serial transmission rate for debug prints
  Serial.begin(9600);
  Serial.println("Initializing Piece Array Scanner");	
}

void loop()
{
  // Scan piece array
  uint64_t board = 0x0000000000000000LL;
  scanPieceArray(&board);	
       
}


void scanPieceArray(uint64_t* board)
{


  long start_time, end_time = 0;
  uchar x, y = 0;
  start_time = millis();
  //Scan the board
  // Run i from 0 to 63
  // *board = 0x0000000000000000LL;


  for(unsigned int i = 0; i < SCAN_SIZE; i++)
    {
      
      
      linTo2D(i, &x, &y);
      //    Serial.print(i);
      //
      //
      //    Serial.print(") Moving .. ");
      //    Serial.print(x,DEC);
      //    Serial.print(",");
      //    Serial.print(y,DEC);

      sig_t col;
      sig_t row;

      
      generateSig(x, &col);
      
      generateSig(y, &row);



      // Decoder = Column
      // Multiplexer = Row
      // One multiplexer per RANK
      // As connected DEMO
      // Enable Decoder
      setDecoder(&col);


      // Enable Multiplexer
      setMux(&row);

      // Wait for settle
      delay(TIME_SETTLE);

      // Read Result
      uchar data = readPieceArrayLine();

      // Save the result
      //      board[i] = data;
      // if(i == 1 || i == 0)
      //setBit(board, data, i);
      //setBit(board,0, 0);
      //setBit(board,0, 1);
      // Serial.print(" -> ");
      // Serial.println(data, DEC);
      tboard[i] = data;
      // Wait for next
      // delay(TIME_NEXT);
    }
  end_time = millis();
  
  Serial.print("Array scan took ");
  Serial.print(end_time-start_time, DEC);
  Serial.println("ms");
  Serial.print("-> ");
  
  /*
    Serial.print(tboard[0], DEC);
    Serial.print(",");
    Serial.println(tboard[1], DEC);
  */
  arrayToBitBoard(tboard, board);

  if(tboard[0] != getBit(board,0) && tboard[1] != getBit(board,1))
    Serial.print("getBitFailure");

  Serial.print(getBit(board,0), DEC);
  Serial.print( ",");
  Serial.println(getBit(board,1), DEC);

}
void arrayToBitBoard(uchar* array, uint64_t* board)
{

  uint64_t temp = 0LL;
  
  for(int i = 0; i < SCAN_SIZE; i++)
    {
      if(array[63-i] == 1)
        {
          // Serial.print(".")
          //  Serial.print((unsigned long int)temp,DEC);
          temp |= 1LL<<i;
        }
    }

  *board = temp;

}
uchar getBit(uint64_t* board, uchar bit)
{
  unsigned long int res = 0L;
  uint64_t hi  = (*board >> 32) & 0x00000000FFFFFFFFLL;
  uint64_t lo =   *board & 0x00000000FFFFFFFFLL;
  // Serial.println("Checking bits");
  //Serial.println(hi,BIN);
  if(bit < 31)
    res = (hi >> (31-bit) )  & 1L;
  else
    {
      bit -=32;
      res = (lo >> (31-bit))  & 1L;
    }
  // Serial.println(hi,BIN);
  //   Serial.print("RES");
  // Serial.println(res,BIN);
  return res;
}
void setBit(uint64_t* board, uchar data, uchar bit)
{
  
  uint64_t board_hi = (*board >> 32)  & 0x00000000FFFFFFFFLL;
  uint64_t  board_lo = *board & 0x00000000FFFFFFFFLL;

  if(data == 0)
    {
      if(bit >= 0 && bit < 32)
        {
          //      Serial.println(bit, DEC);
          //     Serial.println(board_hi,BIN);
          board_hi = board_hi &  ~(1L<<(31-bit));
          //    if(bit == 1)
          //   Serial.println( board_hi,BIN);
        }

 
      else if(bit >=32 && bit < 64)
        {
          bit -= 32;
          board_lo &= ~(1L<<(31-bit));
       
        }
    }
  else if (data == 1)
    {

      if(bit >= 0 && bit < 32)
        {
          //       Serial.println(board_hi, BIN);
          board_hi = board_hi | (1L<<(31-bit));
          //    Serial.println(board_hi,BIN);
        }
      else if(bit >=32 && bit < 64)
        {
          bit -= 32;
          board_lo |= (1L<<(31-bit));
        } 
    
    }
  
  *board  = board_lo | (board_hi << 32);
  delay(10);
  if (getBit(board, bit) != data)
    {
      Serial.print("Got: ");
      Serial.print(getBit(board, bit), BIN);
      Serial.print(" Expected: ");
      Serial.print(data, BIN);
      Serial.println(" Assert setting bit!");
    }
}
int readPieceArrayLine()
{
  return digitalRead(OUT_DATA);
}

void setDecoder(sig_t* s)
{
#ifdef DEBUG
  Serial.print("DEC: ");
  Serial.print(s->m_port1,DEC);
  Serial.print(",");
  Serial.print(s->m_port2,DEC);
  Serial.print(",");
  Serial.println(s->m_port3,DEC);
#endif
  digitalWrite(DEC_PA, s->m_port1);
  digitalWrite(DEC_PB, s->m_port2);
  digitalWrite(DEC_PC, s->m_port3);
  
}



void setMux(sig_t* s)
{ 

  // MAX4581 uses reversed select pins
  // MSB is C LSB is A
  // X0 - 0 0 0 ( C B A)
  // X1 - 0 0 1 ( C B A)

  // Please wire accordingly. 

  /*
    |o   |
    |    |
    |    |
    |    |A
    |    |B
    |____|C

  */

#ifdef DEBUG
  Serial.print("MUX: ");
  Serial.print(s->m_port1,DEC);
  Serial.print(",");
  Serial.print(s->m_port2,DEC);
  Serial.print(",");
  Serial.println(s->m_port3,DEC);
#endif
  digitalWrite(MUX_PA, s->m_port1);
  digitalWrite(MUX_PB, s->m_port2);
  digitalWrite(MUX_PC, s->m_port3);
    
}

void generateSig(uchar i, sig_t* s)
{
  
  uchar a = (i&0x4)>>2;
  uchar b = (i&0x2)>>1;
  uchar c = i&0x1;


  //  printf("%d to bin %d %d %d\n", i, a, b, c);


  s->m_port1 = a;
  s->m_port2 = b;
  s->m_port3 = c;

}

void linTo2D(uchar i, uchar* x, uchar* y)
{
  uchar yt = i/8;
  uchar xt = i%8;

  *x = xt;
  *y = yt;
 
}

