#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Energia.h"

typedef struct {
  int copterY;
} GameState;

GameState * createGameState();

#endif