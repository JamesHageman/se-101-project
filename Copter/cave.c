#include <OrbitOled.h>
#include <OrbitOledGrph.h>
#include "cave.h"
#include "gamestate.h"

void drawCave(GameState *state) {
  int i;
  for (i = 0; i < NUM_CAVE_COLUMNS; i++) {
    int x = i * CAVE_COLUMN_WIDTH;
    int x2 = x + CAVE_COLUMN_WIDTH - 1;
    int topHeight = state->caveColumns[i];

    OrbitOledSetFillPattern(OrbitOledGetStdPattern(1));

    OrbitOledMoveTo(x, 0);
    OrbitOledFillRect(x2, topHeight);

    OrbitOledMoveTo(x, topHeight + CAVE_GAP_HEIGHT);
    OrbitOledFillRect(x2, MAX_HEIGHT - 1);
  }
}