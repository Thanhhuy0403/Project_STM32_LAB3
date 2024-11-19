/*
 * button.c
 *
 *  Created on: Oct 16, 2024
 *      Author: phan thanh huy
 */

#include "button.h"

int KeyReg0[3];
int KeyReg1[3];
int KeyReg2[3];

int KeyReg3[3];
int TimerForKeyPress[3];
int button_flag[3];

GPIO_TypeDef* Button_Ports[3] = {
	Button0_GPIO_Port, Button1_GPIO_Port, Button2_GPIO_Port
};

uint16_t Button_Pins[3] = {
	Button0_Pin, Button1_Pin, Button2_Pin
};

void initButton(){
	for(int i = 0; i < 3; i++){
		KeyReg0[i] = NORMAL_STATE;
		KeyReg1[i] = NORMAL_STATE;
		KeyReg2[i] = NORMAL_STATE;

		KeyReg3[i] = NORMAL_STATE;
		TimerForKeyPress[i] = 200;
	}
	for(int i = 0; i < 3; i++){
		button_flag[i] = 0;
	}
}

int isButtonPressed(int index){
	if(button_flag[index] == 1){
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}

void getKeyInput(){
	for(int i = 0; i < 3; i++){
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
		KeyReg2[i] = HAL_GPIO_ReadPin(Button_Ports[i], Button_Pins[i]);
		if(KeyReg0[i] == KeyReg1[i] && KeyReg1[i] == KeyReg2[i]){
			if(KeyReg3[i] != KeyReg2[i]){
				KeyReg3[i] = KeyReg2[i];
				if(KeyReg2[i] == PRESSED_STATE){
					// TODO
					button_flag[i] = 1;
					TimerForKeyPress[i] = 200;
				}
			}else{
				TimerForKeyPress[i]--;
				if(TimerForKeyPress[i] <= 0){
					KeyReg3[i] = !KeyReg2[i];
				}
			}
		}
	}
}

void run_handleMode(){
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
