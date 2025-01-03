#include "stm32f4xx.h"
#include <stdio.h>

#define GPIOAEN				(1U << 0)
#define PIN5					(1U << 5)
#define LED_PIN				PIN5


int main(void)
{
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA5 to output mode
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

    /* Loop forever */
	while(1)
		{

		// Toggle the LED
			GPIOA->ODR ^= LED_PIN;

			for(int i = 0; i < 100000; i++){}

		}
}
