#include "constants.h"
#include "Energia.h"
#include "gamestate.h"
#include "copter.h"

GameState * createGameState() {
  int i;
  GameState *state = (GameState *) malloc(sizeof(GameState));

  state->copter = createCopter();

  for (i = 0; i < NUM_CAVE_COLUMNS; i++) {
    state->caveColumns[i] = 4;
  }

  return state;
}