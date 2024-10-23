/*
 * trafic_light.c
 *
 *  Created on: Oct 19, 2024
 *      Author: phan thanh huy
 */

#include "trafic_light.h"

int durationLedRed = 5;
int durationLedAmber = 2;
int durationLedGreen = 3;

void onLedRed1(){
	HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 0);
	HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 1);
	HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 1);
}

void onLedAmber1(){
	HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 1);
	HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 0);
	HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 1);
}

void onLedGreen1(){
	HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 1);
	HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 1);
	HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 0);
}

void onLedRed2(){
	HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, 0);
	HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, 1);
	HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, 1);
}

void onLedAmber2(){
	HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, 1);
	HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, 0);
	HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, 1);
}

void onLedGreen2(){
	HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, 1);
	HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, 1);
	HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, 0);
}

void offALL1(){
	HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 1);
	HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 1);
	HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 1);
}

void offALL2(){
	HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, 1);
	HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, 1);
	HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, 1);
}

LedStateToggle currentLed = LED_ON;
void togglelLed(int duration){
	switch (currentLed) {
		case LED_ON:
			HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 0);
			HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 0);
			HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 0);
			if(timer_flag[2] == 1){
				currentLed = LED_OFF;
				setTimer(2, 500);
			}
			break;
		case LED_OFF:
			HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 1);
			HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 1);
			HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 1);
			if(timer_flag[2] == 1){
				currentLed = LED_ON;
				setTimer(2, 500);
			}
			break;
		default:
			break;
	}
}


void runTraficLight1(){
	switch (status){
		case INIT:
			offALL1();
			setTimer(0, durationLedRed*1000);
			setTime7SEG(durationLedRed);
			handleTime1();
			setTimer(4, 1000);

			status = AUTO_LED_RED;
			break;
		case AUTO_LED_RED:
			onLedRed1();
			if(timer_flag[0] == 1){
				status = AUTO_LED_GREEN;
				setTimer(0, durationLedGreen*1000);
				setTime7SEG(durationLedGreen);
				handleTime1();
				setTimer(4, 1000);
			}
			break;
		case AUTO_LED_GREEN:
			onLedGreen1();
			if(timer_flag[0] == 1){
				status = AUTO_LED_AMBER;
				setTimer(0, durationLedAmber*1000);
				setTime7SEG(durationLedAmber);
				handleTime1();
				setTimer(4, 1000);
			}
			break;
		case AUTO_LED_AMBER:
			onLedAmber1();
			if(timer_flag[0] == 1){
				status = AUTO_LED_RED;
				setTimer(0, durationLedRed*1000);
				setTime7SEG(durationLedRed);
				handleTime1();
				setTimer(4, 1000);
			}
			break;
		default:
			break;
	}
}

