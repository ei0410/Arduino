#include <SPI.h>  
#include <Pixy.h>
#include <ZumoMotors.h>
#include "ServoLoop.h"
 
#define X_CENTER    160L
#define Y_CENTER    100L
#define RCS_MIN_POS     0L
#define RCS_MAX_POS     1000L
#define RCS_CENTER_POS  ((RCS_MAX_POS-RCS_MIN_POS)/2)
 
Pixy pixy;
 
ServoLoop panLoop(200, 200);
ServoLoop tiltLoop(150, 200);
 
ZumoMotors motors;

void setup()
{
  Serial.begin(9600);
  Serial.print("Starting...\n");

  panLoop.setServoLoop(RCS_MIN_POS, RCS_CENTER_POS, RCS_MAX_POS);
  tiltLoop.setServoLoop(RCS_MIN_POS, RCS_CENTER_POS, RCS_MAX_POS); 
  pixy.init();
}
 
uint32_t lastBlockTime = 0;
 
void loop()
{ 
  uint16_t blocks;
  blocks = pixy.getBlocks();
 
  if (blocks)
  {
    int trackedBlock = TrackBlock(blocks);
    FollowBlock(trackedBlock);
    lastBlockTime = millis();
  }  
  else if (millis() - lastBlockTime > 100)
  {
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);
    ScanForBlocks();
  }
}
 
int oldX, oldY, oldSignature;

int TrackBlock(int blockCount)
{
  int trackedBlock = 0;
  long maxSize = 0;
 
  Serial.print("blocks =");
  Serial.println(blockCount);
 
  for (int i = 0; i < blockCount; i++)
  {
    if ((oldSignature == 0) || (pixy.blocks[i].signature == oldSignature))
    {
      long newSize = pixy.blocks[i].height * pixy.blocks[i].width;
      if (newSize > maxSize)
      {
        trackedBlock = i;
        maxSize = newSize;
      }
    }
  }
 
  int32_t panError = X_CENTER - pixy.blocks[trackedBlock].x;
  int32_t tiltError = pixy.blocks[trackedBlock].y - Y_CENTER;
 
  panLoop.update(panError);
  tiltLoop.update(tiltError);
 
  pixy.setServos(panLoop.getServoLoop(), tiltLoop.getServoLoop());
 
  oldX = pixy.blocks[trackedBlock].x;
  oldY = pixy.blocks[trackedBlock].y;
  oldSignature = pixy.blocks[trackedBlock].signature;
  return trackedBlock;
}

int32_t size = 400;

void FollowBlock(int trackedBlock)
{
  int32_t followError = RCS_CENTER_POS - panLoop.getServoLoop();

  size += pixy.blocks[trackedBlock].width * pixy.blocks[trackedBlock].height; 
  size -= size >> 3;
 
  int forwardSpeed = constrain(400 - (size/256), -100, 400);  
 
  int32_t differential = (followError + (followError * forwardSpeed))>>8;

  int leftSpeed = constrain(forwardSpeed + differential, -400, 400);
  int rightSpeed = constrain(forwardSpeed - differential, -400, 400);

  motors.setLeftSpeed(leftSpeed);
  motors.setRightSpeed(rightSpeed);
}

int scanIncrement = (RCS_MAX_POS - RCS_MIN_POS) / 150;
uint32_t lastMove = 0;
 
void ScanForBlocks()
{
  if (millis() - lastMove > 20)
  {
    lastMove = millis();
    panLoop.updateServoLoop(scanIncrement);
    if ((panLoop.getServoLoop() >= RCS_MAX_POS)||(panLoop.getServoLoop() <= RCS_MIN_POS))
    {
      tiltLoop.updateServoLoop(random(RCS_MAX_POS * 0.6, RCS_MAX_POS));
      scanIncrement = -scanIncrement;
      if (scanIncrement < 0)
      {
        motors.setLeftSpeed(-250);
        motors.setRightSpeed(250);
      }
      else
      {
        motors.setLeftSpeed(+180);
        motors.setRightSpeed(-180);
      }
      delay(random(250, 500));
    }
 
    pixy.setServos(panLoop.getServoLoop(), tiltLoop.getServoLoop());
  }
}
