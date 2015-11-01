#ifndef COPTER_H
#define COPTER_H

typedef struct {
  double x;
  double y;
} Copter;

Copter *createCopter();

void drawCopter(Copter *copter);

#endif