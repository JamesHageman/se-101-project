#include <OrbitOled.h>
#include <OrbitOledGrph.h>
#include "cave.h"
#include "gamestate.h"
#include "constants.h"

void drawCave(GameState *state) {
  int start = (int)state->cavePosition % MAX_WIDTH;
  int i;
  for (i = 0; i < NUM_CAVE_COLUMNS; i++) {
    int x = (MAX_WIDTH + i * CAVE_COLUMN_WIDTH - start) % MAX_WIDTH;
    int x2 = x + CAVE_COLUMN_WIDTH;
    int topHeight = state->caveColumns[i];
    int bottomHeight = topHeight + CAVE_GAP_HEIGHT;

    OrbitOledSetFillPattern(OrbitOledGetStdPattern(1));

    OrbitOledMoveTo(x, topHeight);
    OrbitOledLineTo(x2, topHeight);

    OrbitOledMoveTo(x, bottomHeight);
    OrbitOledLineTo(x2, bottomHeight);

    if (x2 < MAX_WIDTH) {
      // Draw vertical lines joining columns
      int nextTopHeight = state->caveColumns[(i + 1) % NUM_CAVE_COLUMNS];
      OrbitOledMoveTo(x2, topHeight);
      OrbitOledLineTo(x2, nextTopHeight);

      OrbitOledMoveTo(x2, bottomHeight);
      OrbitOledLineTo(x2, nextTopHeight + CAVE_GAP_HEIGHT);
    }
  }
}