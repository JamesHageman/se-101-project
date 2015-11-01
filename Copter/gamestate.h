#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Energia.h"
#include "copter.h"

typedef struct {
  Copter *copter;
} GameState;

GameState * createGameState();

#endif