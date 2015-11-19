#include <OrbitBoosterPackDefs.h>
#include "print.h"

//Function to print the game over screen
void printGameOver(long score) {
  char scoreString[50];// = "Score: ";
  sprintf(scoreString, "Score: %d", score);
  OrbitOledClear();
  OrbitOledSetCursor(3, 0);
  OrbitOledPutString("Game Over!");
  OrbitOledSetCursor(3, 2.5);
  OrbitOledPutString(scoreString);
}

//Function to print the start menu of the game
void printStart() {
  OrbitOledClear();
  OrbitOledSetCursor(0, 0);
  OrbitOledPutString("Push Any Button To Start Game");
}

void ledControl (int led, int state) {
  switch (led) {
    case 1:
      GPIOPinWrite(LED1Port, LED1, (state)?(LED1):(LOW));
      break;
    case 2:
      GPIOPinWrite(LED2Port, LED2, (state)?(LED2):(LOW));
      break;
    case 3:
      GPIOPinWrite(LED3Port, LED3, (state)?(LED3):(LOW));
      break;
    case 4:
      GPIOPinWrite(LED4Port, LED4, (state)?(LED4):(LOW));
      break;
  }
}
