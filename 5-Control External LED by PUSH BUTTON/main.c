#define SYSCTL_RCGCGPIO_R   (*((volatile int *) 0x400FE608))   
#define GPIO_PORTB_DEN_R    (*((volatile int *) 0x4000551C))
#define GPIO_PORTB_DIR_R    (*((volatile int *) 0x40005400))
#define GPIO_PORTB_DATA_R   (*((volatile int *) 0x40005030))
#define GPIO_PORTB_AMSEL_R  (*((volatile int *) 0x40005528))
#define GPIO_PORTB_AFSEL_R  (*((volatile int *) 0x40005420))
#define GPIO_PORTB_PCTL_R   (*((volatile int *) 0x4000552C))
#define GPIO_PORTB_PUR_R    (*((volatile int *) 0x40005510))
#define GPIO_PORTB_LOCK_R   (*((volatile int *) 0x40005520))
#define GPIO_PORTB_CR_R     (*((volatile int *) 0x40005524))

#define GPIO_PORTB_CLK_EN  0x02      //enable clock for PORTB
#define GPIO_PORTB_PIN2_EN 0x04			 //enable pin 2 of PORTB
#define GPIO_PORTB_PIN3_EN 0x08			 //enable pin 3 of PORTB

#define LED_ON2            0x04			 //turn on  LED on Pin 2 PORTB
#define LED_OFF2           0x00			 //turn off  LED on Pin 2 PORTB


void Delay(unsigned int);
void PORTB_Init(void);

int main(void)
{
	unsigned int SW;
	PORTB_Init();
	while(1)
	{
		SW = GPIO_PORTB_DATA_R & 0x08;
		if(!SW)
		{
			GPIO_PORTB_DATA_R = LED_ON2;    //Turn on Blue LED 	
		}
		else
		{
			GPIO_PORTB_DATA_R = LED_OFF2;   //Turn  off LED
		}
	}
}

void Delay(unsigned int delay)
{
	volatile unsigned int i, counter;
	counter = delay * 4000;  // 1 second (1000 msec) needs 40000000 counter so 4000000/1000 = 4000
	for(i=0;i<counter;i++);
}

void PORTB_Init(void)
{
	SYSCTL_RCGCGPIO_R |= GPIO_PORTB_CLK_EN;           //activate clock for Port A
  Delay(10);           															//Delay 10 msec to allow clock to start on PORTB  
	GPIO_PORTB_LOCK_R = 0x4C4F434B;           				//unlock GPIO of PORTB
	GPIO_PORTB_CR_R = 0x01;                   				//Enable GPIOPUR register enable to commit
	GPIO_PORTB_PUR_R |= GPIO_PORTB_PIN3_EN;   				//Enable Pull Up SW on PA3	
  GPIO_PORTB_DEN_R |= GPIO_PORTB_PIN2_EN;        	  // Enable pin 2 of PORTB 
	GPIO_PORTB_DEN_R |= GPIO_PORTB_PIN3_EN;        	  // Enable pin 3 of PORTB 
  GPIO_PORTB_DIR_R |= GPIO_PORTB_PIN2_EN;        	  // Make pin 2 of PORTB as ouptut pin
	GPIO_PORTB_PCTL_R &= ~GPIO_PORTB_PIN2_EN ; 				// Regular GPIO of PORTB
  GPIO_PORTB_AMSEL_R &= ~GPIO_PORTB_PIN2_EN;        // Disable analog function on pin 2 of PORTB
	GPIO_PORTB_AFSEL_R &= ~GPIO_PORTB_PIN2_EN;        // Regular port function
	GPIO_PORTB_PCTL_R &= ~GPIO_PORTB_PIN3_EN ; 				// Regular GPIO of PORTB
  GPIO_PORTB_AMSEL_R &= ~GPIO_PORTB_PIN3_EN;        // Disable analog function on pin 3 of PORTB
	GPIO_PORTB_AFSEL_R &= ~GPIO_PORTB_PIN3_EN;        // Regular port function
}

