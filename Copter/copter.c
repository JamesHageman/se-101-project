#include <LaunchPad.h>
#include "copter.h"
#include <OrbitOled.h>
#include <OrbitOledGrph.h>
#include "constants.h"

/*
Copter:

 ***
  *
****
 */

char CopterBmp[] = {
  0b00000100,
  0b00000101,
  0b00000111,
  0b00000101
};

const int CopterWidth = 4;
const int CopterHeight = 3;

Copter *createCopter()  {
  Copter *c = malloc(sizeof(Copter));
  c->x = MAX_WIDTH / 5;
  c->y = MAX_HEIGHT / 2;
  return c;
}

void drawCopter(Copter *copter) {
  int x = (int) copter->x;
  int y = (int) copter->y;

  OrbitOledMoveTo(x, y);
  OrbitOledPutBmp(CopterWidth, CopterHeight, CopterBmp);
  // OrbitOledDrawRect(16, 4);
}