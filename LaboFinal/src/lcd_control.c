/*
 * lcd_control.c
 *
 *  Created on: 15 nov. 2021
 *      Author: Matheus
 */


#include "lcd_control.h"

volatile unsigned int lcdInit = 0;

void configureLcdGPIO(void)
{

	// activer clocks des GPIOs B, D et timer 2
	RCC->AHB1ENR |= BIT1 | BIT3;
	RCC->APB1ENR |= BIT0;

	// configurer pins instruction LCD output
	GPIOB->MODER |= BIT6 | BIT8 | BIT10;
	GPIOB->MODER &= ~(BIT7 | BIT9 | BIT11);

	//configurer pins donnees LCD output
	setLcdBusOutput();

}

void setLcdBusOutput(void)
{
	// mettre bus en monde sortie
	GPIOD->MODER |= BIT0 | BIT2 | BIT4 | BIT6 | BIT8 | BIT10 | BIT12 | BIT14;
	GPIOD->MODER &= ~(BIT1 | BIT3 | BIT5 | BIT7 | BIT9 | BIT11 | BIT13 | BIT15);
}

void setLcdBusInput(void)
{
	// mettre bus en monde sortie
	GPIOD->MODER &= ~(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7 | BIT8 | BIT9 | BIT10 | BIT11 | BIT12 | BIT13 | BIT14 | BIT15);
}

void delay(int cycles){
	for(volatile int wait_var = 0; wait_var < cycles; wait_var++){}
}

unsigned char checkBusyFlag(void)
{
	setLcdBusInput();

	GPIOB->ODR |= (BIT_EN | BIT_RW);	// Enable ON, RS to high
	GPIOB->ODR &= ~BIT_RS;
	
	unsigned char result = (GPIOD->IDR & BIT_D7);
	
	return result;
}

void writeLCD(int p_package)
{
	setLcdBusOutput();

	GPIOB->ODR |= (BIT_EN | BIT_RS);	// Enable ON, RS to high
	GPIOB->ODR &= ~BIT_RW;

	GPIOD->ODR = (GPIOD->ODR & 0xFFFFFF00) | (p_package & 0xFF);		//print p_package


	delay(100);

	GPIOB->ODR &= ~BIT_EN;	// Enable OFF
	GPIOB->ODR &= ~BIT_RS;
	GPIOB->ODR |= BIT_RW;


    unsigned char flag = 0;
    if((lcdInit = 0)){delay(10000);}
    else{flag = checkBusyFlag();}

    while (flag)
    {
        flag = checkBusyFlag();
    }
}

void instructLCD(int p_package)
{
	setLcdBusOutput();

	GPIOB->ODR &= ~(BIT_RS | BIT_RW); //RS and RW to 0
	GPIOB->ODR |= BIT_EN;	// Enable ON

	GPIOD->ODR = (GPIOD->ODR & 0xFFFFFFF00) | (p_package & 0xFF);		//print p_package


	delay(100);
	GPIOB->ODR &= ~BIT_EN;	// Enable OFF
	GPIOB->ODR |= (BIT_RS | BIT_RW);

    unsigned char flag = 0;
    if((lcdInit = 0)){delay(10000);}
    else{flag = checkBusyFlag();}

    while (flag)
    {
        flag = checkBusyFlag();
    }
    
	
}

void configureLCD(void)
{
	//INIT SEQ.

	for(int iter = 0; iter < 4; iter++)
	{
		instructLCD(0x38);
	}

	instructLCD(0x01);	// Display clear
	instructLCD(0x0E);	// Display control (0x0C to erase cursor, 0x0E to display cursor)
	writeLCD(0x52);		// print R
	writeLCD(0x50);		// print P
	writeLCD(0x4D);		// print M
	writeLCD(0x3A);		// print :
	instructLCD(0xC0);	// 2nd line
	writeLCD(0x56);		// print V
	writeLCD(0x70);		// print p
	writeLCD(0x74);		// print t
	writeLCD(0x3A);		// print :

    lcdInit = 1;

}

void writeInfo(float p_value)
{
	instructLCD(0x8F);	// set cursor
	instructLCD(0x04);	// set left shift
	setLcdBusOutput();

	unsigned int firstValue = (int)p_value;
	unsigned int secondValue = (int)((p_value - firstValue)*100);

	if (secondValue > 10)
	{
		writeLCD(secondValue);
		writeLCD('0');
	} else {
		for(int i = 0; i <= 3;i++)
		{ 
			int value = secondValue % 10;
			secondValue /= 10;

			writeLCD(value + '0');
		}
	}

	writeLCD(0x2E);

	for(int i = 0; i <= 3;i++)
	{
		int value = firstValue % 10;
		firstValue /= 10;

		writeLCD(value + '0');
	}

	instructLCD(0x06);	// set right shift
}
