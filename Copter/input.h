#ifndef INPUT_H
#define INPUT_H

#include "gamestate.h"
#include <FillPat.h>
#include <I2CEEPROM.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>

#include  "delay.h"

void readSensorData(GameState* state);

#endif