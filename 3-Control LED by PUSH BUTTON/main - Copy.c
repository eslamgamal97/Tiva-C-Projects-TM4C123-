# define SYSCTL_RCGCGPIO_R (*(( volatile int *)0x400FE608))
# define GPIO_PORTF_DATA_RD (*(( volatile int *)0x40025040)) 
# define GPIO_PORTF_DATA_WR (*(( volatile int *)0x40025010)) 
# define GPIO_PORTF_DIR_R (*(( volatile int *)0x40025400)) 
# define GPIO_PORTF_DEN_R (*(( volatile int *)0x4002551C))
# define GPIO_PORTF_PUR_R (*(( volatile int *)0x40025510 ))

# define SYSCTL_RCGC2_GPIOF 0x20
# define GPIO_PORTF_PIN2_EN 0x04
# define GPIO_PORTF_PIN4_EN 0x10
# define SYSTEM_CLOC_FREQUENCY  16000000

#define DELAY_DEBOUNCE					SYSTEM_CLOC_FREQUENCY/1000

void Delay(unsigned long counter);	

int main ()
{
	static char flag = 0; 
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOF;
	GPIO_PORTF_DEN_R |= GPIO_PORTF_PIN2_EN +GPIO_PORTF_PIN4_EN;
	GPIO_PORTF_DIR_R |= GPIO_PORTF_PIN2_EN; 
	GPIO_PORTF_DIR_R &= ~(GPIO_PORTF_PIN4_EN);
	GPIO_PORTF_PUR_R |= GPIO_PORTF_PIN4_EN;
	
while(1)
{
	if(GPIO_PORTF_DATA_RD == 0)
	{
		Delay(DELAY_DEBOUNCE);
		if(( flag == 0) && (GPIO_PORTF_DATA_RD == 0))
		{
			GPIO_PORTF_DATA_WR ^= GPIO_PORTF_PIN2_EN;
			flag = 1;
		}
	}
	else
	{
		flag = 0; 
	}
}
}

void Delay(unsigned long counter)
{
	unsigned long i = 0;
	for(i = 0; i<counter; i++);	
}
