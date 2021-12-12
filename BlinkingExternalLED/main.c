#define SYSCTL_RCGCGPIO_R   (*((volatile int *) 0x400FE608))   
#define GPIO_PORTA_DEN_R    (*((volatile int *) 0x4000451C))
#define GPIO_PORTA_DIR_R    (*((volatile int *) 0x40004400))
#define GPIO_PORTA_DATA_R   (*((volatile int *) 0x40004010))
#define GPIO_PORTA_AMSEL_R  (*((volatile int *) 0x40004528))
#define GPIO_PORTA_AFSEL_R  (*((volatile int *) 0x40004420))
#define GPIO_PORTA_PCTL_R   (*((volatile int *) 0x4000452C))


#define GPIO_PORTA_CLK_EN  0x01      //enable clock for PORTA
#define GPIO_PORTA_PIN2_EN 0x04			 //enable pin 2 of PORTA

#define LED_ON2            0x04			 //turn on  LED on Pin 2 PORTA
#define LED_OFF2           0x00			 //turn off  LED on Pin 2 PORTA


void Delay(unsigned int);

int main(void)
{
	SYSCTL_RCGCGPIO_R |= GPIO_PORTA_CLK_EN;           //activate clock for Port A
  Delay(10);           															//Delay 10 msec to allow clock to start on PORTA                  
  GPIO_PORTA_DEN_R |= GPIO_PORTA_PIN2_EN;        	  // Enable pin 2 of PORTA 
  GPIO_PORTA_DIR_R |= GPIO_PORTA_PIN2_EN;        	  // Make pin 2 of PORTA as ouptut pin
	GPIO_PORTA_PCTL_R &= ~GPIO_PORTA_PIN2_EN; 				// Regular GPIO of PORTA
  GPIO_PORTA_AMSEL_R &= ~GPIO_PORTA_PIN2_EN;        // Disable analog function on pin 2 of PORTA
	GPIO_PORTA_AFSEL_R &= ~GPIO_PORTA_PIN2_EN;        // Regular port function

	
	while(1)
	{
		GPIO_PORTA_DATA_R = LED_ON2;    //Turn on Blue LED 	 
		Delay(1000);	                  //Delay almost 1 sec
		GPIO_PORTA_DATA_R = LED_OFF2;   //Turn  off LED
		Delay(1000);                    //Delay almost 1 sec
	}
}

void Delay(unsigned int delay)
{
	volatile unsigned int i, counter;
	counter = delay * 4000;  // 1 second (1000 msec) needs 40000000 counter so 4000000/1000 = 4000
	for(i=0;i<counter;i++);
}


