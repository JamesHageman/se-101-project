#include "Energia.h"
#include "gamestate.h"
#include "update.h"
#include "constants.h"

void updateGameLogic(GameState *state, double deltaTime) {

  state->cavePosition += 10 * deltaTime;

  state->copter->y += 0.1 * state->accelY*deltaTime;
  //copter at bottom stays at bottom
  if (state->copter->y > MAX_HEIGHT - 3) {
    state->copter->y = MAX_HEIGHT - 3;
  }
  //copter at top stays at top
  if (state->copter->y < 3) {
    state->copter->y = 3;
  }
    
  //collision detection alogirthm here
    int coptH = 3;
    int coptW = 4;
    
    
}
