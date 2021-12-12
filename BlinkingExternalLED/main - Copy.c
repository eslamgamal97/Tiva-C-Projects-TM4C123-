#define SYSCTL_RCGCGPIO_R   (*((volatile int *) 0x400FE608))
#define GPIO_PORTA_DEN_R    (*((volatile int *) 0x4000451C))
#define GPIO_PORTA_DIR_R    (*((volatile int *) 0x40004400))
#define GPIO_PORTA_DATA_R   (*((volatile int *) 0x40004010))
#define GPIO_PORTA_AMSEL_R  (*((volatile int *) 0x40004528))
#define GPIO_PORTA_AFSEL_R  (*((volatile int *) 0x40004420))
#define GPIO_PORTA_PCTL_R   (*((volatile int *) 0x4000452C))


/*#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define PA2                     (*((volatile unsigned long *)0x40004010))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
*/
#define GPIO_PORTA_CLK_EN  0x01
#define GPIO_PORTA_PIN2_EN 0x04

#define LED_ON2            0x04

#define DELAY_VALUE        4000000   

void Delay(void);

int main(void)
{
	volatile int delay;
	SYSCTL_RCGCGPIO_R |= 0x01;           // 1) activate clock for Port A
  delay = SYSCTL_RCGCGPIO_R;           // allow time for clock to start
                                    // 2) no need to unlock PA2
  
  GPIO_PORTA_DIR_R |= 0x04;         // 5) set direction to output
  GPIO_PORTA_DEN_R |= 0x04;         // 7) enable digital port
	GPIO_PORTA_PCTL_R &= ~0x04; // 3) regular GPIO
  GPIO_PORTA_AMSEL_R &= ~0x04;      // 4) disable analog function on PA2
	GPIO_PORTA_AFSEL_R &= ~0x04;      // 6) regular port function

	
	while(1)
	{
		GPIO_PORTA_DATA_R = 0x04;    //Turn on RED LED 	 
		Delay();	                   //Delay almost 1 sec
		GPIO_PORTA_DATA_R = 0x00;    //Turn  off LED
		Delay();                     //Delay almost 1 sec
	}
}

void Delay(void)
{
	volatile unsigned long i;
	for(i=0;i<DELAY_VALUE;i++);
}


