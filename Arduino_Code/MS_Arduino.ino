#include <Pixy.h>
//#include <PixyI2C.h>
#include <PixySPI_SS.h>
//#include <PixyUART.h>
#include <Wire.h>
#include <TPixy.h>

Pixy pixy;
//PixyI2C pixy(0x54);
int blocks;
int marbleSignature;

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);  

  Serial.print("Starting...\n");
  pixy.init();//initializing pixy
}


void loop() {
  // put your main code here, to run repeatedly:
  blocks = pixy.getBlocks();
  marbleSignature = pixy.blocks[0].signature; //get the signature color
  
  if((blocks < 2)&&(blocks))
  {
    if((pixy.blocks[0].width/pixy.blocks[0].height > 0.8) && (pixy.blocks[0].width/pixy.blocks[0].height < 1.2))
    {
      if(marbleSignature == 1)
      {
        Serial.write(1);
        delay(1000);
      }
      else if(marbleSignature == 2)
      {
        Serial.write(2);
        delay(1000);
      }
    }
  }
  else
  {
    Serial.write(3);
    delay(1000);
  }
  
}
