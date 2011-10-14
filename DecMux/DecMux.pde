/*
  Pins 7,6,5,4,3,2 -> outputs
       7, 6, 5 => Decoder 
       4, 3, 2 => Multiplexer
       
  Pin 8 <- Inputs


*/
const int INPUT_PIN = 8;

const int COL_A = 7;
const int COL_B = 6;
const int COL_C = 5;

const int ROW_A = 4;
const int ROW_B = 3;
const int ROW_C = 2;

void setup() {                
  // Initialize ouput pins and input
  pinMode(COL_A, OUTPUT); 
  pinMode(COL_B, OUTPUT);
  pinMode(COL_C, OUTPUT);
  pinMode(ROW_A, OUTPUT);
  pinMode(ROW_B, OUTPUT);
  pinMode(ROW_C, OUTPUT);
  
  pinMode(INPUT_PIN, INPUT);
  digitalWrite(INPUT_PIN, LOW);
  Serial.begin(9600);
  
}
int sensorVal = 0;
int who = 0;

void loop()
{
  sensorVal = digitalRead(INPUT_PIN);
         // wait for a secondsecond
  
  digitalWrite(COL_A, LOW);
  digitalWrite(COL_B, LOW);
  digitalWrite(COL_C, LOW);
  
  if(who%2 == 0)
  {
     Serial.print(" HALL ");
     digitalWrite(ROW_A, LOW);
     digitalWrite(ROW_B, LOW);
     digitalWrite(ROW_C, LOW);
    for(int i = 0; i < 20; i++)
    {
 
       sensorVal = digitalRead(INPUT_PIN);
     
        Serial.print(sensorVal);
        Serial.print(".");
        
    }
    Serial.println("");
    delay(3000);
}
  else
  {
      
  
  Serial.print(" REED ");
  digitalWrite(ROW_A, HIGH);
  digitalWrite(ROW_B, LOW);
  digitalWrite(ROW_C, LOW);
  

  for(int i = 0; i < 20; i++)
  {
 

    sensorVal = digitalRead(INPUT_PIN);
    Serial.print(sensorVal);
    Serial.print(".");

  }
  delay(3000);
  Serial.println("");
  }
 
 who++;
 if(who > 100)
   who = 0;
  
  
}
