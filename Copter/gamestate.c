#include "Energia.h"
#include "gamestate.h"

GameState * createGameState() {
  GameState *state = (GameState *) malloc(sizeof(GameState *));
  return state;
}