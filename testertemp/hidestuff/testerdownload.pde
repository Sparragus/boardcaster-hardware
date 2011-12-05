#include <WProgram.h>
#include "testertemp.h"
void setup()
{
  Serial.begin(9600);
  Serial.println("Blah");

  Serial.println("termine");
}

void loop()
{
  initPoster();
  Serial.println("init done");
  setNextFEN("3k3r/8/8/8/8/8/1K6/RNBP4 w KQkq - 0 1");
  sendData();
  delay(100000);


}
