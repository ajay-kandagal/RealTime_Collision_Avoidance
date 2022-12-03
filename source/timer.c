/*******************************************************************************
 * @file	timer.c
 * @brief 	Initializes SysTick timer to generate interrupt for every 1 second
 *
 * @author 	Ajaykumar Kandagal, ajka9053@colorado.edu
 * @data 	Nov 23, 2022
 ******************************************************************************/
#include "timer.h"


// 3MHz external clock frequency
#define EXT_CLOCK_FREQUENCY 	(3000000U)
#define TIMER_RESOLUTION_MS 	(10)


volatile uint32_t elapsed_time = 0;


/*******************************************************************************
 * Initializes SysTick timer to generate interrupts at every 1 second.
 ******************************************************************************/
void init_systick()
{
	NVIC_DisableIRQ(SysTick_IRQn);

	// Loading value to generate interrupt at every 1 second
	SysTick->LOAD = ((EXT_CLOCK_FREQUENCY - 1) * TIMER_RESOLUTION_MS) / 1000;

	// Force timer to reload the value
	SysTick->VAL = 0;

	// Enable SysTick and its interrupt flag
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

	// Set SysTick timer priority
	NVIC_SetPriority(SysTick_IRQn, 2);

	// Clear any pending SysTick IRQs
	NVIC_ClearPendingIRQ(SysTick_IRQn);

	// Enable NVIC interrupt flag
	NVIC_EnableIRQ(SysTick_IRQn);
}


/*******************************************************************************
 * Returns elapsed time in 10ms resolution
 *
 * Return:
 *   Returns total elapsed time in milliseconds
 ******************************************************************************/
uint32_t get_time_ms()
{
	return (elapsed_time * TIMER_RESOLUTION_MS);
}


void delay_ms(uint32_t ms)
{
	uint32_t now_time = elapsed_time;
	while((elapsed_time - now_time) * TIMER_RESOLUTION_MS < ms );
}


/*******************************************************************************
 * Interrupt handler for systick timer underflow. Sets the overflow flag.
 ******************************************************************************/
void SysTick_Handler()
{
	NVIC_DisableIRQ(SysTick_IRQn);

	elapsed_time++;

	NVIC_EnableIRQ(SysTick_IRQn);
}
