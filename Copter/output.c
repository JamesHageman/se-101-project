#include "Energia.h"
#include "output.h"

void ledControl (int led, int state) {
  switch (led) {
    case 1:
      GPIOPinWrite(LED1Port, LED1, (state)?(LED1):(LOW));
      break;
    case 2:
      GPIOPinWrite(LED2Port, LED2, (state)?(LED2):(LOW));
      break;
    case 3:
      GPIOPinWrite(LED3Port, LED3, (state)?(LED3):(LOW));
      break;
    case 4:
      GPIOPinWrite(LED4Port, LED4, (state)?(LED4):(LOW));
      break;
  }
}
