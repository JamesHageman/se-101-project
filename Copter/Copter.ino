extern "C" {
  #include <FillPat.h>
  #include <I2CEEPROM.h>
  #include <LaunchPad.h>
  #include <OrbitBoosterPackDefs.h>
  #include <OrbitOled.h>
  #include <OrbitOledChar.h>
  #include <OrbitOledGrph.h>

  #include "delay.h"

  #include "gamestate.h"
  #include "copter.h"
  #include "input.h"
  #include "cave.h"
  #include "update.h"
  #include "print.h"
}

clock_t lastTime = NULL;
GameState *state;

// Magical code that makes the accelerometer work
bool I2CGenIsNotIdle() {
  return !I2CMasterBusBusy(I2C0_BASE);
}
char I2CGenTransmit(char * pbData, int cSize, bool fRW, char bAddr) {
  int i;
  char *pbTemp;
  pbTemp = pbData;
  /*Start*/
  /*Send Address High Byte*/
  /* Send Write Block Cmd
  */
  I2CMasterSlaveAddrSet(I2C0_BASE, bAddr, WRITE);
  I2CMasterDataPut(I2C0_BASE, *pbTemp);
  I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
  DelayMs(1);
  /* Idle wait
  */
  while(I2CGenIsNotIdle());
  /* Increment data pointer
  */
  pbTemp++;
  /*Execute Read or Write*/
  if(fRW == READ) {
    /* Resend Start condition
    ** Then send new control byte
    ** then begin reading
    */
    I2CMasterSlaveAddrSet(I2C0_BASE, bAddr, READ);
    while(I2CMasterBusy(I2C0_BASE));
    /* Begin Reading
    */
    for(i = 0; i < cSize; i++) {
      if(cSize == i + 1 && cSize == 1) {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
        DelayMs(1);
        while(I2CMasterBusy(I2C0_BASE));
      }
      else if(cSize == i + 1 && cSize > 1) {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
        DelayMs(1);
        while(I2CMasterBusy(I2C0_BASE));
      }
      else if(i == 0) {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
        DelayMs(1);
        while(I2CMasterBusy(I2C0_BASE));
        /* Idle wait
        */
        while(I2CGenIsNotIdle());
      }
      else {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        DelayMs(1);
        while(I2CMasterBusy(I2C0_BASE));
        /* Idle wait
        */
        while(I2CGenIsNotIdle());
      }
      while(I2CMasterBusy(I2C0_BASE));
      /* Read Data
      */
      *pbTemp = (char)I2CMasterDataGet(I2C0_BASE);
      pbTemp++;
    }
  }
  else if(fRW == WRITE) {
    /*Loop data bytes
    */
    for(i = 0; i < cSize; i++) {
      /* Send Data
      */
      I2CMasterDataPut(I2C0_BASE, *pbTemp);
      while(I2CMasterBusy(I2C0_BASE));
      if(i == cSize - 1) {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
        DelayMs(1);
        while(I2CMasterBusy(I2C0_BASE));
      }
      else {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
        DelayMs(1);
        while(I2CMasterBusy(I2C0_BASE));
        /* Idle wait
        */
        while(I2CGenIsNotIdle());
      }
      pbTemp++;
    }
  }
  /*Stop*/
  return 0x00;
}

void setup()  {
  /*
   * First, Set Up the Clock.
   * Main OSC		  -> SYSCTL_OSC_MAIN
   * Runs off 16MHz clock -> SYSCTL_XTAL_16MHZ
   * Use PLL		  -> SYSCTL_USE_PLL
   * Divide by 4	  -> SYSCTL_SYSDIV_4
   */
  SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_4);

  /*
   * Enable and Power On All GPIO Ports
   */
  //SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOA | SYSCTL_PERIPH_GPIOB | SYSCTL_PERIPH_GPIOC |
  //						SYSCTL_PERIPH_GPIOD | SYSCTL_PERIPH_GPIOE | SYSCTL_PERIPH_GPIOF);

  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOA );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOB );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOC );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOD );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOE );
  SysCtlPeripheralEnable(	SYSCTL_PERIPH_GPIOF );
  /*
   * Pad Configure.. Setting as per the Button Pullups on
   * the Launch pad (active low).. changing to pulldowns for Orbit
   */
  GPIOPadConfigSet(SWTPort, SWT1 | SWT2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

  GPIOPadConfigSet(BTN1Port, BTN1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
  GPIOPadConfigSet(BTN2Port, BTN2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

  GPIOPadConfigSet(LED1Port, LED1, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED2Port, LED2, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED3Port, LED3, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED4Port, LED4, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);

  /*
   * Initialize Switches as Input
   */
  GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);

  /*
   * Initialize Buttons as Input
   */
  GPIOPinTypeGPIOInput(BTN1Port, BTN1);
  GPIOPinTypeGPIOInput(BTN2Port, BTN2);

  /*
   * Initialize LEDs as Output
   */
  GPIOPinTypeGPIOOutput(LED1Port, LED1);
  GPIOPinTypeGPIOOutput(LED2Port, LED2);
  GPIOPinTypeGPIOOutput(LED3Port, LED3);
  GPIOPinTypeGPIOOutput(LED4Port, LED4);

  /*
   * Enable ADC Periph
   */
  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

  GPIOPinTypeADC(AINPort, AIN);

  /*
   * Enable ADC with this Sequence
   * 1. ADCSequenceConfigure()
   * 2. ADCSequenceStepConfigure()
   * 3. ADCSequenceEnable()
   * 4. ADCProcessorTrigger();
   * 5. Wait for sample sequence ADCIntStatus();
   * 6. Read From ADC
   */
  ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
  ADCSequenceEnable(ADC0_BASE, 0);

  /*
   * Initialize the OLED
   */
  OrbitOledInit();

  /*
   * Enable I2C Peripheral
   */
  SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
  SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

  /*
   * Set I2C GPIO pins
   */
  GPIOPinTypeI2C(I2CSDAPort, I2CSDA_PIN);
  GPIOPinTypeI2CSCL(I2CSCLPort, I2CSCL_PIN);
  GPIOPinConfigure(I2CSCL);
  GPIOPinConfigure(I2CSDA);

  /*
   * Setup I2C
   */
  I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

  /* Initialize the Accelerometer
   *
   */
  GPIOPinTypeGPIOInput(ACCL_INT2Port, ACCL_INT2);

  srand(0);
  state = createGameState();
    createCave(state);

    long lBtn1;
    long lBtn2;
    printStart();

    do {
      lBtn1 = GPIOPinRead(BTN1Port, BTN1);
      lBtn2 = GPIOPinRead(BTN2Port, BTN2);
    } while (lBtn1 != BTN1 && lBtn2 != BTN2);
}

void render() {
  // OrbitOledClear();
  OrbitOledMoveTo(0,0);
  OrbitOledSetCursor(0,0);

  OrbitOledSetFillPattern(OrbitOledGetStdPattern(0));
  OrbitOledFillRect(MAX_WIDTH, MAX_HEIGHT);
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(1));

  drawCopter(state->copter);
  shiftCave(state);
  drawCave(state);

  OrbitOledUpdate();
}

void loop()  {
  // This is how deltaTime should work - but I can't get the clock() to compile

  // clock_t currentTime = clock();
  // double deltaTime;
  // if (!lastTime) {
  //   deltaTime = 0.0;
  // } else {
  //   deltaTime = (double)(currentTime - lastTime) / CLOCKS_PER_SEC;
  // }

  // lastTime = currentTime;

  int SPEED = (state->Ptnt);

  readSensorData(state);
  updateGameLogic(state, (2.0 - SPEED/10) / 20); // For now, assume 20 FPS

  //If collision is detected (gameover)
  if (state->gameOver == 1)
  {
    printGameOver((long) state->score);
    delay(5000);
    setup();
  }

  render();
  delay(10-SPEED);
}
