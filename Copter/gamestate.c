#include "Energia.h"
#include "gamestate.h"
#include "copter.h"

GameState * createGameState() {
  GameState *state = (GameState *) malloc(sizeof(GameState));

  state->copter = createCopter();

  return state;
}