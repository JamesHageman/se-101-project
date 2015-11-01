#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Energia.h"
#include "copter.h"
#include "constants.h"

typedef struct {
  Copter *copter;
  int caveColumns[NUM_CAVE_COLUMNS];
} GameState;

GameState * createGameState();

#endif