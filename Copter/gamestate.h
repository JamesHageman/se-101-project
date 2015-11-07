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
} GameState;

GameState * createGameState();

#endif
