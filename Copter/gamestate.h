#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Energia.h"
#include "copter.h"
#include "constants.h"

typedef struct {
  // Copter Object
  Copter *copter;

  // Cave Related
  int caveColumns[NUM_CAVE_COLUMNS];
  char caveObject[MAX_HEIGHT][MAX_WIDTH];
  int obstacleOnScreen;
  int cavePosition;

  // Sensors
  // Accelerometer
  double accelY;
  int accelInitialized;

  // Switches and Buttons
  long Swt1;
  long Swt2;
  long Btn1;
  long Btn2;

  // Potentiometer
  unsigned long Ptnt;

  // GameOver
  int gameOver;

  // Score
  long score;

} GameState;

GameState * createGameState();

#endif
