#include "Energia.h"
#include "update.h"

int brightness = 0;
int fadeAmount = 5;

void updateGameLogic(GameState *state, double deltaTime) {
  if ( ((int)state->score % 50) < 10) srand((unsigned int)(state->accelY*10));

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

    analogWrite(GREEN_LED, brightness);    
    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;

    // reverse the direction of the fading at the ends of the fade: 
    if (brightness == 0 || brightness == 255) {
      fadeAmount = -fadeAmount ; 
    }
  } else {
    analogWrite(GREEN_LED, 0);
  }

  // update score
  state->score += (state->Ptnt / 10.0)*1; // modified by speed of game

  // give people reating room
  if (state->score < 50) state->gameOver = 0;

  // I LIKE IT WHEN THE LEDS LIGHT UP FAM
  if (state->score > 100) ledControl(4,1);
  else ledControl(4,0);

  if (state->score > 500) ledControl(3,1);
  else ledControl(3,0);

  if (state->score > 1000) ledControl(2,1);
  else ledControl(2,0);

  if (state->score > 2000) ledControl(1,1);
  else ledControl(1,0);
}
