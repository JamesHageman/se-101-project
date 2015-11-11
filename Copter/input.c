#include "Energia.h"
#include "input.h"

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






void readSensorData(GameState* state) {
  // ACCELEROMETOR VOODOO {
  short dataX;
  short dataY;
  short dataZ;

  char chPwrCtlReg = 0x2D;
  char chX0Addr = 0x32;
  char chY0Addr = 0x34;
  char chZ0Addr = 0x36;

  char rgchReadAccl [] = {0, 0, 0};
  char rgchReadAccl2[] = {0, 0, 0};
  char rgchReadAccl3[] = {0, 0, 0};

  if(state->accelInitialized == 0){
    char rgchWriteAccl[] = {0, 0};
    rgchWriteAccl[0] = chPwrCtlReg;
    rgchWriteAccl[1] = 1 << 3;    // sets Accl in measurement mode
    I2CGenTransmit(rgchWriteAccl, 1, WRITE, ACCLADDR);
    state->accelInitialized = 1;
  }

  rgchReadAccl[0] = chX0Addr;
  rgchReadAccl2[0] = chY0Addr;
  rgchReadAccl3[0] = chZ0Addr;

  I2CGenTransmit(rgchReadAccl, 2, READ, ACCLADDR);
  I2CGenTransmit(rgchReadAccl2, 2, READ, ACCLADDR);
  I2CGenTransmit(rgchReadAccl3, 2, READ, ACCLADDR);

  dataX = (rgchReadAccl[2] << 8) | rgchReadAccl[1];
  dataY = (rgchReadAccl2[2] << 8) | rgchReadAccl2[1];
  dataZ = (rgchReadAccl3[2] << 8) | rgchReadAccl2[1];

  state->accelY = dataY;
  // } ACCELEROMETOR VOODOO OVER

  // Get button state
  state->Swt1 = GPIOPinRead(SWT1Port, SWT1);
  state->Swt2 = GPIOPinRead(SWT2Port, SWT2);
  state->Btn1 = GPIOPinRead(BTN1Port, BTN1);
  state->Btn2 = GPIOPinRead(BTN2Port, BTN2);

  // Get Potentiometer State
  ADCProcessorTrigger(ADC0_BASE, 0);
  while(!ADCIntStatus(ADC0_BASE, 0, false));
  ADCSequenceDataGet(ADC0_BASE, 0, &(state->Ptnt));

  // Potentiometer is a ulong from ~0 to ~10
  // less than 10, slightly more than 0
  state->Ptnt = state->Ptnt/400;
}