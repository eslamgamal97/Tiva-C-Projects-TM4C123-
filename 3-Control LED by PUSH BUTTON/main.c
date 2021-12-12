#define SYSCTL_RCGCGPIO_R  (*((volatile int *) 0x400FE608))
#define GPIO_PORTF_DIR_R   (*((volatile int *) 0x40025400))
#define GPIO_PORTF_DEN_R   (*((volatile int *) 0x4002551C))
#define GPIO_PORTF_DATA_R  (*((volatile int *) 0x4002507C))
#define GPIO_PORTF_PUR_R   (*((volatile int *) 0x40025510))
#define GPIO_PORTF_LOCK_R  (*((volatile int *) 0x40025520))
#define GPIO_PORTF_CR_R    (*((volatile int *) 0x40025524))
	
#define GPIO_PORTF_CLK_EN  0x20    //clock enable of PORTF
#define GPIO_PORTF_PIN1_EN 0x02    //Enable RED LED
#define GPIO_PORTF_PIN4_EN 0x10    //Enable SW1



int main(void)
{
	SYSCTL_RCGCGPIO_R |= GPIO_PORTF_CLK_EN;   //enable clock of PORTF
	GPIO_PORTF_LOCK_R = 0x4C4F434B;           //unlock GPIO of PORTF
	GPIO_PORTF_CR_R = 0x01;                   //Enable GPIOPUR register enable to commit
	GPIO_PORTF_PUR_R |= GPIO_PORTF_PIN4_EN;   //Enable Pull Up SW1
	GPIO_PORTF_DIR_R |= GPIO_PORTF_PIN1_EN;   //Make PF1 as output and PF4 as input by default
	GPIO_PORTF_DEN_R |= GPIO_PORTF_PIN1_EN + GPIO_PORTF_PIN4_EN; //enable PF1 and PF4 pins as digital GPIO 
	
	while(1)
	{
		if(GPIO_PORTF_DATA_R & 0x10)
		{
			GPIO_PORTF_DATA_R = 0x00;                 //turn off RED LED
		}

		else
		{
			GPIO_PORTF_DATA_R = GPIO_PORTF_PIN1_EN;   //turn on RED LED
		}
	}
}





