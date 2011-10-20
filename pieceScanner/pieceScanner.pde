


#include "config.h"
void scanPieceArray(uchar* board);
void linTo2D(uchar i, uchar* x, uchar* y);
void generateSig(uchar i, sig_t* s);
void setDecoder(sig_t* s);
void setMux(sig_t* s);
int readPieceArrayLine();



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
  uchar board[64];
  scanPieceArray(board);	
       
}


void scanPieceArray(uchar* board)
{



  uchar x, y = 0;
		
  //Scan the board
  // Run i from 0 to 63
  for(unsigned int i = 0; i < 64; i++)
    {
      
      i = 0;
      linTo2D(i, &x, &y);
      Serial.print(i);
      Serial.print(") Moving .. ");
      Serial.print(x,DEC);
      Serial.print(",");
      Serial.print(y,DEC);

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
      board[i] = data;
      Serial.print(" -> ");
      Serial.println(data, DEC);

      // Wait for next
      delay(TIME_NEXT);
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

