/*
 * pwm.c
 *
 *  Created on: 11 déc. 2021
 *      Author: eti52
 */
#include "pwm.h"

void configureTIM2(float p_frequence){
  volatile int sys_clk = 53760000; //syscoreclk
  volatile int prescaler_1 = 500; // 1 to 512
  volatile int prescaler_2 = 2; // prescaller_2 % prescaler_3 = 4/2 = 2
  volatile float dutycycle = 0.10;

  RCC->APB1ENR |= BIT0; // donne horloge au peripherique TIM2


  TIM2->CR1 &= ~BIT0; // counter disable
  TIM2->CR1 &= ~BIT4; // upcounter

  TIM2->DIER |= BIT0; // update interupt enable
  TIM2->DIER |= BIT1; // update compare enable

  TIM2->PSC = prescaler_1; //set prescaller
  ARR = ((sys_clk/(prescaler_1 * prescaler_2))/(p_frequence));
  TIM2->ARR = ARR; // max value du reload -- sets frequency

  TIM2->CCER |= BIT0; // enable compare
  TIM2->CCMR1 &= ~BIT1;
  TIM2->CCMR1 &= ~BIT0; // 00 output config
  TIM2->CCMR1 |= BIT6;
  TIM2->CCMR1 |= BIT5;
  TIM2->CCMR1 &= ~BIT4; // 110 mode PWM 1
  TIM2->CCMR1 |= BIT3; // preload enable

  TIM2->CCR1 = ARR * dutycycle; // width of pwm -- sets dutycycle
  TIM2->CR1 |= BIT7; //ARPE auto preload enable

  NVIC->ISER[0] |= BIT28; // activate TIM2 in NVIC pour quil puisse traiter les interupt

  TIM2->CR1 |= BIT0; // counter enable
}

void setPWM(float p_dutycycle){
	//TIM2->CR1 |= BIT0;
	if (p_dutycycle > 1) p_dutycycle = 1.0;
	if (p_dutycycle < 0.04) p_dutycycle = 0.04;

	TIM2->CCR1 = ARR * p_dutycycle; // width of pwm -- sets dutycycle
}

void configureGPIOLED(){
	RCC->AHB1ENR |= BIT3; // donne horloge au peripherique GPIOD

	GPIOD->MODER |= BIT30; // set mode de input output
	GPIOD->MODER &= ~BIT31;

	GPIOD->MODER |= BIT28; // set mode de input output
	GPIOD->MODER &= ~BIT29;

	GPIOD->MODER |= BIT26; // set mode de input output
	GPIOD->MODER &= ~BIT27;

	GPIOD->MODER |= BIT24; // set mode de input output
	GPIOD->MODER &= ~BIT25;
}
