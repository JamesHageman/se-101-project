#ifndef CAVE_H
#define CAVE_H

#include "gamestate.h"
#include "constants.h"
//Cave object that we use for logic:

void drawCave(GameState *state);
void createCave(GameState *state);
void shiftCave(GameState *state);
#endif