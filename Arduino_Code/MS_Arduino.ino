// Main arduino code with comms (I2C, UART) and pass Pixy info to VEX

#include <Wire.h>
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 10; i++)
  {
    Serial.write('3');
    //Serial.print('1');
    delay(500);
  }
  
}
