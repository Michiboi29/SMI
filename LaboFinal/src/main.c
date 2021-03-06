/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2021-12-11

The MIT License (MIT)
Copyright (c) 2019 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"
#include "macros_utiles.h"
#include "pwm.h"
#include "adc.h"
#include "dac.h"
#include "exti.h"
#include "timer.h"
#include "lcd_control.h"

/* Private macro */
/* Private variables */
volatile float dutyCycle = 0;
volatile long extiCount = 0;
volatile long lastExtiCount = 0;
volatile long timeCount = 0;
volatile long lastTimeCount = 0;
/* Private function prototypes */
/* Private functions */

void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~BIT0; // update interupt flag to 0
	timeCount++;
}

// Handle PB12 interrupt
void EXTI15_10_IRQHandler(void) {
	EXTI->PR |= BIT12; // update flag exti
	GPIOD->ODR ^= BIT13;
	extiCount++;
}

float calculateSpeed(){
	int tickTurn = 12;
	long diffExti = extiCount - lastExtiCount;
	float diffSpace = (float)diffExti / tickTurn;
	float diffTime = (float)(timeCount - lastTimeCount)/1000;
	lastExtiCount = extiCount;
	lastTimeCount = timeCount;
	float return_value = diffSpace/diffTime;
	return return_value;
}


/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
  int i = 0;
  volatile uint16_t val;
  volatile float dutyVal;
  volatile float speed;
  /**
  *  IMPORTANT NOTE!
  *  The symbol VECT_TAB_SRAM needs to be defined when building the project
  *  if code has been located to RAM and interrupts are used. 
  *  Otherwise the interrupt table located in flash will be used.
  *  See also the <system_*.c> file and how the SystemInit() function updates 
  *  SCB->VTOR register.  
  *  E.g.  SCB->VTOR = 0x20000000;  
  */

  /* TODO - Add your application code here */

  configureGPIOPWM();
  configureGPIOADC();
  configureGPIOEXTI();
  configureLcdGPIO();
  configureLCD();
  configureTIM2(1567);
  configureTIM3(1000);
  configureADC();
  configureDAC();
  configureEXTI();

  /* Infinite loop */
  while (1)
  {
	i++;


	val = readADC(0); // val de 16 bits (/4095) et va de 0V a ~3V (Vref)
	dutyVal = (float)val/4095.0;
	if (val <= 0) dutyVal = 0;
	setPWM(dutyVal);

	long diffTime_main = timeCount - lastTimeCount;
	if (diffTime_main > 700){
		speed = calculateSpeed();
		writeInfo(speed);
	}
  }
}
