// Code by Gabriel J. Perez
//         Francisco De La Cruz

//Pin connected to S-IN of IR2D07
int dataPin = 8;
//Pin connected to CLK of IR2D07
int clockPin = 9;
//Pin connected to LATCH of IR2D07
int latchPin = 10;
//Pin connected to XEN of IR2D07
int xenPin = 11;

unsigned int j = 0;
const int disp[] = { 0, 1, 2, 3};

void setup() {
    //set pins to output so you can control the shift register
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(xenPin, OUTPUT);
  
    digitalWrite(latchPin, HIGH);
  
}

void loop() {
   

        // Set xenPin high to disable the drivers.
        // Set the latch low to allow data through latch. This might
        // have to be revised.
        digitalWrite(xenPin, HIGH);
        digitalWrite(latchPin, LOW);

        // Set the clockPin low to prepare for rising edge trigger
        digitalWrite(clockPin, LOW);  
        // Shift out the data
        shiftOut(dataPin, clockPin, MSBFIRST, disp[j] );  
        
        // Index overflow housekeeping
        j++;
        if(j>3)
            j = 0;
     
        // Set latch high to capture latch
        // Set xenPin low to enable the drivers
        // Set latchPin low to allow data to pass through
        digitalWrite(latchPin, HIGH);
        digitalWrite(xenPin, LOW);
        digitalWrite(latchPin, LOW);

        // Delay about 1sec per number    
        delay(1000);
   
}

