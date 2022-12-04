/*
 * warning_tone.h
 *
 *  Created on: 03-Dec-2022
 *      Author: ajayk
 */
#ifndef BUZZER_H_
#define BUZZER_H_


void buzzer_init();
void play_buzzer(uint16_t target_val, uint16_t max_val);
void stop_buzzer();


#endif /* BUZZER_H_ */
