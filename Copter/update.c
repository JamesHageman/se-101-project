#include "Energia.h"
#include "gamestate.h"
#include "update.h"
#include "constants.h"

void updateGameLogic(GameState *state, double deltaTime) {
  state->copter->y += 4 * deltaTime;
  if (state->copter->y > MAX_HEIGHT - 3) {
    state->copter->y = 0;
  }
}