#include "Energia.h"
#include "input.h"

//void readSensorData(GameState* state) {
//  short	dataX;
//  
//  if(fClearOled == true) {
//    OrbitOledClear();
//    OrbitOledMoveTo(0,0);
//    OrbitOledSetCursor(0,0);
//    fClearOled = false;
//
//    /*
//     * Enable I2C Peripheral
//     */
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
//    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
//
//    /*
//     * Set I2C GPIO pins
//     */
//    GPIOPinTypeI2C(I2CSDAPort, I2CSDA_PIN);
//    GPIOPinTypeI2CSCL(I2CSCLPort, I2CSCL_PIN);
//    GPIOPinConfigure(I2CSCL);
//    GPIOPinConfigure(I2CSDA);
//
//    /*
//     * Setup I2C
//     */
//    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
//
//    /* Initialize the Accelerometer
//     *
//     */
//    GPIOPinTypeGPIOInput(ACCL_INT2Port, ACCL_INT2);
//
//    rgchWriteAccl[0] = chPwrCtlReg;
//    rgchWriteAccl[1] = 1 << 3;		// sets Accl in measurement mode
//    I2CGenTransmit(rgchWriteAccl, 1, WRITE, ACCLADDR);
//
//  }
//  
//  rgchReadAccl[0] = chX0Addr;
//    I2CGenTransmit(rgchReadAccl, 2, READ, ACCLADDR);
//
//    dataX = (rgchReadAccl[2] << 8) | rgchReadAccl[1];
//    state->accelY = dataX;
//
//    /*
//     * Check and see if Accel is positive or negative
//     * and set fDir accordingly
//     */
//    if(dataX < 0 && dataX < xDirThreshNeg) {
//      fDir = true;
//
//      if(xcoRocketCur >= (ccolOledMax - 32)) {
//        xcoRocketCur = 0;
//
//        /*
//	 * Clear the Oled
//         */
//        OrbitOledClear();
//      }
//
//      else {
//        xcoRocketCur++;
//      }
//
//      RocketRight(xcoRocketCur, ycoRocketCur);
//    }
//
//    else if(dataX > 0 && dataX > xDirThreshPos) {
//      fDir = false;
//
//      if(xcoRocketCur <= 0) {
//        xcoRocketCur = ccolOledMax - 32;
//
//        /*
//	 * Clear the Oled
//         */
//        OrbitOledClear();
//      }
//
//      else {
//        xcoRocketCur--;
//      }
//
//      RocketLeft(xcoRocketCur, ycoRocketCur);
//    }
//
//    else {
//      RocketStop(xcoRocketCur, ycoRocketCur, fDir);
//    }
//  }
//
//}
