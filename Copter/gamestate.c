#include "constants.h"
#include "Energia.h"
#include "gamestate.h"
#include "copter.h"
#include <stdlib.h>

GameState * createGameState() {
  int i;
  GameState *state = (GameState *) malloc(sizeof(GameState));

  state->copter = createCopter();

  for (i = 0; i < NUM_CAVE_COLUMNS; i++) {
    state->caveColumns[i] = rand() % CAVE_MAX_COLUMN_HEIGHT;
  }

  return state;
}