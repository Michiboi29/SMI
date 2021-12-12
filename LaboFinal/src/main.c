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

/* Private macro */
/* Private variables */
volatile float dutyCycle = 0.90;
/* Private function prototypes */
/* Private functions */

void TIM2_IRQHandler (void){
	  TIM2->SR &= ~BIT0; // update interupt flag to 0
	  TIM2->SR &= ~BIT1; // compare/capture interrupt flag to 0
	  GPIOD->ODR ^= BIT15; // switch to on/off

//	  changePWM(dutyCycle);
//	  if (dutyCycle >= 1) dutyCycle = 0;
//	  dutyCycle = dutyCycle + 0.1/2;
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
  volatile uint16_t valTemp;

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

  configureGPIOLED();
  configureGPIOADC();
  configureTIM2(2000);
  configureADC();
  configureChannelADC();


  /* Infinite loop */
  while (1)
  {
	i++;
	valTemp = readADC();
	val = valTemp;
  }
}
