#include "TM4C123.h"                    // Device header

void timer0A_delayMs(int ttime); /*multiple of msec delay using periodic mode */

int main(void)
{
	SYSCTL->RCGCGPIO |= 0x20;   /*enable clock to GPIOF */
	GPIOF->DIR = 0x0E;					/*enable GPIO pins of PORTF as OUTPUT */
	GPIOF->DEN = 0x0E;					/*enable GPIO pins of PORTF as digital functions */
	
	
	while(1)
	{
			GPIOF->DATA = 2;          /*turn on RED LED */
			timer0A_delayMs(1000);    /*TimerA 1000 msec delay */
			GPIOF->DATA = 0;          /*turn off RED LED */
			timer0A_delayMs(1000);    /*TimerA 1000 msec delay */
	}
}

void timer0A_delayMs(int ttime)
{
	volatile int i;
	SYSCTL->RCGCTIMER |= 1;                 /*enable clock for TimerA */
	TIMER0->CTL = 0;												/*disable timer before initialization */
	TIMER0->CFG = 0x04;											/*16-bit option */
	TIMER0->TAMR = 0x02;                    /*periodic mode and down counter */
	TIMER0->TAILR = 16000 - 1;              /*TimerA interval load value register */
	TIMER0->ICR = 0x01;                     /*clear the TimerA timeout flag */
	TIMER0->CTL |= 0x01;                    /*enable TimerA after initialization */
	for(i=0;i<ttime;i++)
	{
		while((TIMER0->RIS & 0x01) == 0);     /*wait for TimerA timeout flag */
		TIMER0->ICR = 0x01;                   /*clear the TimerA timeout flag */
	}
}


