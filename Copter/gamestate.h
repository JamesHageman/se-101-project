#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Energia.h"
#include "copter.h"
#include "constants.h"

typedef struct {
  Copter *copter;
  int caveColumns[NUM_CAVE_COLUMNS];
  char caveObject[MAX_HEIGHT][MAX_WIDTH];
    int obstacleOnScreen;
  int cavePosition;
  double accelY;
  int accelInitialized;

  long Swt1;
  long Swt2;
  long Btn1;
  long Btn2;

  unsigned long ulAIN0;

} GameState;

GameState * createGameState();

#endif
