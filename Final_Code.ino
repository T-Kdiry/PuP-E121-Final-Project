#include <ArduinoInit.h>
#include <SendOnlySoftwareSerial.h>

                                //Beacon light when closer to a light is approx 8000 or less

int startColor;                 //Left Sensor when next to a light is approx 6000 or less
int floorColor;
int currentSide;
int side;
int firstSide;



void setup() {
  configArduino();
  attachInterrupt (0, leftBumperHit, LOW);
  attachInterrupt (1, rightBumperHit, LOW);
  outputHigh(4);
  whichSide();
  side = whichSide();
  
}

void loop() {
  whichSide();
  
  if(whichSide() == side) {
   moveOtherSide();
   } else {
   enemySide();
   }

   if (readInput(2) == 0) {
    outputHigh(10);
    rightBumperHit();
   }

   if (readInput(3) == 0) {
    outputHigh(10);
    leftBumperHit();
   }
  }


void motorsOff()
{
  motors('b','o', 0);
  pause(500);
  return;
}

void moveBack()
{
  motors('b', 'b', 100);
  pause(1000);
  return;
}

void goForward () {
  motors('b', 'a', 80);
  pause(4000);
}

void rightBumperHit ()
{
      motorsOff();
      moveBack();
      pause(100);
      motors('1', 'b', 100);
      motors('2', 'o', 0);
      pause(300);
      motorsOff();
      goForward();
}

void leftBumperHit ()
{
      motorsOff();
      moveBack();
      pause(100);
      motors('2', 'b', 100);
      motors('1', 'o', 0);
      pause(300);
      motorsOff();
      goForward();
}

void moveOtherSide()
{
    if(whichSide() == side) {
      if(readADC(0) > 13300) {
        motors('1', 'a', 100);
        motors('2', 'o', 0);
      } else if (readADC(0) < 13300) {
        goForward();
      }
  }
  return;
}

int whichSide()
{
  int side;
  if(readADC(2) < 25000) {
    side = 1;
  } else if(readADC(2) > 25000) {
    side = 0;
  }
  return side;
}
 
void enemySide()
{

  if(readADC(1) < 8000 && readADC(3) > 7000) {
    motorsOff();
    motors('2', 'a', 100);
    motors('1', 'o', 0);
    pause(500);
    motors('b', 'a', 100);
    pause(3000);
  } else if(readADC(3) < 7000 && readADC(1) > 8000) {
    motorsOff();
    motors('1', 'a', 100);
    motors('2', 'o', 0);
    pause(500);
    motors('b', 'a', 100);
    pause(3000);
  } else if (readADC(3) < 7000 && readADC(1) < 8000) {
    goForward();
  }
}

