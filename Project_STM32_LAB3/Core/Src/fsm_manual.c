/*
 * fsm_manual.c
 *
 *  Created on: Nov 19, 2024
 *      Author: phan thanh huy
 */

#include "fsm_manual.h"

void fsm_manual(){
	switch (status){
		case AUTO_LED_RED:
		case AUTO_LED_AMBER:
		case AUTO_LED_GREEN:
			if(timer_flag[4] == 1){
				setTimer(4, 1000);
				handleTime1();
			}
			if(timer_flag[6] == 1){
				setTimer(6, 1000);
				handleTime2();
			}
			if(isButtonPressed(0) == 1){
				status = MODE_1;
				status2 = MODE_1;
				setTimer(0, 0);
				setTimer(1, 10000);		// Timer MODE
				setTimer(2, 200); 		// Timer toggle
				setTime7SEG1(durationLedRed);
				update7SEGBuffer1();
			}
			break;
		case MODE_1:
			togglelLed(200, LED_RED);
			led_buffer[2] = 0;
			led_buffer[3] = 1;
			if(timer_flag[1] == 1 || isButtonPressed(2)){
				status = INIT;
				status2 = INIT;
				setTimer(2, 0);
			}
			if(isButtonPressed(1) == 1){
				durationLedRed++;
				if(durationLedRed > 99){
					durationLedRed = 1;
				}
				setTime7SEG1(durationLedRed);
				update7SEGBuffer1();
				setTimer(1, 10000);
			}
			if(isButtonPressed(0) == 1){
				status = MODE_2;
				status2 = MODE_2;
				setTimer(1, 10000);
				setTime7SEG1(durationLedGreen);
				update7SEGBuffer1();
			}
			break;
		case MODE_2:
			togglelLed(200, LED_GREEN);
			led_buffer[2] = 0;
			led_buffer[3] = 2;
			if(timer_flag[1] == 1 || isButtonPressed(2)){
				status = INIT;
				setTimer(2, 0);
			}
			if(isButtonPressed(1) == 1){
				durationLedGreen++;
				if(durationLedGreen > 99){
					durationLedGreen = 1;
				}
				setTime7SEG1(durationLedGreen);
				update7SEGBuffer1();
				setTimer(1, 10000);
			}
			if(isButtonPressed(0) == 1){
				status = MODE_3;
				status2 = MODE_3;
				setTimer(1, 10000);
				setTime7SEG1(durationLedAmber);
				update7SEGBuffer1();
			}
			break;
		case MODE_3:
			togglelLed(200, LED_AMBER);
			led_buffer[2] = 0;
			led_buffer[3] = 3;
			if(timer_flag[1] == 1 || isButtonPressed(2)){
				status = INIT;
				status2 = INIT;
				setTimer(2, 0);
			}
			if(isButtonPressed(1) == 1){
				durationLedAmber++;
				if(durationLedAmber > 9){
					durationLedAmber = 1;
				}
				setTime7SEG1(durationLedAmber);
				update7SEGBuffer1();
				setTimer(1, 10000);
			}
			if(isButtonPressed(0) == 1){
				status = INIT;
				status2 = INIT;
				setTimer(1, 10000);
			}
			break;
		default:
			break;
	}
}

