#include "Energia.h"
#include "gamestate.h"
#include "update.h"

void updateGameLogic(GameState *state, double deltaTime) {
  state->copter->x += 6 * deltaTime;
  if (state->copter->x > 100) {
    state->copter->x = 0;
  }
}