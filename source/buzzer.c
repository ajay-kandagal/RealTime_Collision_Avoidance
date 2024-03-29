/*
 * warning_tone.c
 *
 *  Created on: 03-Dec-2022
 *      Author: ajayk
 */
#include "MKL25Z4.h"
#include "buzzer.h"


#define BUZZER_PIN 			(0)
#define BUZZER_PORT 		(PORTD)
#define BUZZER_SCGC5_MASK 	(SIM_SCGC5_PORTD_MASK)
#define TPM_CHANNEL 		(0)
#define TPM_SCGC6_MASK 		(SIM_SCGC6_TPM0_MASK)

#define CPU_CLOCK_FREQ			(48000000)
#define TPM_PRESCALER_BIN_VAL 	(7)
#define TPM_PRESCALER_VAL		(128)

#define MIN_BUZZER_FREQ			(200)
#define MAX_BUZZER_FREQ			(4000)
#define BUZZER_FREQ_STEPS		(5)

#define MIN_TPM_MOD_VAL			((CPU_CLOCK_FREQ / MAX_BUZZER_FREQ) / TPM_PRESCALER_VAL)
#define MAX_TPM_MOD_VAL			((CPU_CLOCK_FREQ / MIN_BUZZER_FREQ) / TPM_PRESCALER_VAL)
#define TPM_MOD_RANGE			(MAX_TPM_MOD_VAL - MIN_TPM_MOD_VAL)
#define TPM_MOD_RESOLUTION		(TPM_MOD_RANGE / BUZZER_FREQ_STEPS)

void buzzer_init()
{
	SIM->SCGC5 |= BUZZER_SCGC5_MASK;
	SIM->SCGC6 |= TPM_SCGC6_MASK;

	BUZZER_PORT->PCR[BUZZER_PIN] &= ~((uint32_t) PORT_PCR_MUX_MASK);
	BUZZER_PORT->PCR[BUZZER_PIN] |= ((uint32_t) PORT_PCR_MUX(4));

	// Set to use external clock source for TPM
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	TPM0->SC = TPM_SC_PS(TPM_PRESCALER_BIN_VAL);
	TPM0->CONF |= TPM_CONF_DBGMODE(3);
	TPM0->CONTROLS[TPM_CHANNEL].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

	// Enabling PWM control
	TPM0->SC &= ~TPM_SC_CMOD(1);
}

void stop_buzzer()
{
	if (TPM0->SC & TPM_SC_CMOD(1))
		TPM0->SC &= ~TPM_SC_CMOD(1);
}

void play_buzzer(uint16_t target_val, uint16_t max_val)
{
	uint16_t tmp_mod_val = (TPM_MOD_RANGE / max_val) * target_val;
	tmp_mod_val = (tmp_mod_val / TPM_MOD_RESOLUTION) * TPM_MOD_RESOLUTION;
	TPM0->MOD = MIN_TPM_MOD_VAL + tmp_mod_val;
	TPM0->CONTROLS[TPM_CHANNEL].CnV = TPM0->MOD / 2;			// 50% duty cycle
	TPM0->SC |= TPM_SC_CMOD(1);
}
