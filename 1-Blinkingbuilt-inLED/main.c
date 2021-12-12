#define SYSCTL_RCGCGPIO_R (*((volatile unsigned long *) 0x400FE608))
#define GPIO_PORTF_DEN_R  (*((volatile unsigned long *) 0x4002551C))
#define GPIO_PORTF_DIR_R  (*((volatile unsigned long *) 0x40025400))
#define GPIO_PORTF_DATA_R (*((volatile unsigned long *) 0x40025038))

	 
#define GPIO_PORTF_CLK_EN  0x20
#define GPIO_PORTF_PIN1_EN 0x02
#define GPIO_PORTF_PIN2_EN 0x04
#define GPIO_PORTF_PIN3_EN 0x08
#define LED_ON1            0x02
#define LED_ON2            0x04
#define LED_ON3            0x08

#define DELAY_VALUE        4000000   

void Delay(void);

int main(void)
{
	SYSCTL_RCGCGPIO_R |= GPIO_PORTF_CLK_EN;     //enable clock for PORTF
	GPIO_PORTF_DEN_R  |= GPIO_PORTF_PIN1_EN;    //enable pins 1 on PORTF
	GPIO_PORTF_DIR_R  |= GPIO_PORTF_PIN1_EN;    //make pins 1 as output pins
	GPIO_PORTF_DEN_R  |= GPIO_PORTF_PIN2_EN;    //enable pins 2 on PORTF
	GPIO_PORTF_DIR_R  |= GPIO_PORTF_PIN2_EN;    //make pins 2 as output pins
	GPIO_PORTF_DEN_R  |= GPIO_PORTF_PIN3_EN;    //enable pins 3 on PORTF
	GPIO_PORTF_DIR_R  |= GPIO_PORTF_PIN3_EN;    //make pins 3 as output pins
	
	while(1)
	{
		GPIO_PORTF_DATA_R = 0x02;    //Turn on RED LED 	 
		Delay();	                   //Delay almost 1 sec
		GPIO_PORTF_DATA_R = 0x00;    //Turn  off LED
		Delay();                     //Delay almost 1 sec
	}
}

void Delay(void)
{
	volatile unsigned long i;
	for(i=0;i<DELAY_VALUE;i++);
}
