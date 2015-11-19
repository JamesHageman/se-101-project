#include "Energia.h"
#include "gamestate.h"
#include "update.h"
#include "constants.h"
#include "output.h"

void updateGameLogic(GameState *state, double deltaTime) {
  //state->cavePosition += 10 * deltaTime;

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

  int dx, dy;
  int y = (state->copter->y);
  int x = (state->copter->x);
  for (dx = 0; dx < coptW; dx++) {
    for (dy = 0; dy < coptH; dy++) {
      if (state->caveObject[y + dy][x + dx] == '#') state->gameOver = 1;
    }
  }

  if (state->Swt1 != 0) { // having switch 1 on == GODMODE!
    state->gameOver = 0;
  }

  // if (state->gameOver) {
  //   ledControl(4,1);
  // } else ledControl(4,0);

  // update score
  state->score += (state->Ptnt / 10.0)*1; // modified by speed of game

  // I LIKE IT WHEN LEDS LIGHT UP FAM
  if (state->score > 200) ledControl(4,1);
  else ledControl(4,0);

  if (state->score > 400) ledControl(3,1);
  else ledControl(3,0);

  if (state->score > 600) ledControl(2,1);
  else ledControl(2,0);

  if (state->score > 800) ledControl(1,1);
  else ledControl(1,0);
}
