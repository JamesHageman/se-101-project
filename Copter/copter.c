#include "copter.h"
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>

// Still gotta figure out how the fuck this bmp shit works
char CopterBmp[] = {
  0b11100000, 0b1010000, 0b11100000, 0, 0, 0, 0, 0
};

const int CopterWidth = 8;
const int CopterHeight = 8;

void drawCopter(GameState *state) {
  OrbitOledMoveTo(0, 0);
  OrbitOledSetCursor(0, state->copterY);
  OrbitOledPutBmp(CopterWidth, CopterHeight, CopterBmp);
}