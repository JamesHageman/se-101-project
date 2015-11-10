#include "constants.h"
#include "Energia.h"
#include "gamestate.h"
#include "copter.h"
#include <stdlib.h>

GameState * createGameState() {
  GameState *state = (GameState *) malloc(sizeof(GameState));

  state->cavePosition = 0;
  state->caveObject;
    state->obstacleOnScreen = 0;
  state->copter = createCopter();

  // Sensor Data
  // Accelerometer
  state->accelInitialized = 0;
  state->accelY = 0;

  // Switches
  state->Swt1 = 0;
  state->Swt2 = 0;

  // Buttons
  state->Btn1 = 0;
  state->Btn2 = 0;

  // Potentiometer
  state->ulAIN0 = 0;

  return state;
}
