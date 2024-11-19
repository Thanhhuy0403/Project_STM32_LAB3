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
void togglelLed(int duration, ledType led){
	switch (currentLed) {

		case LED_ON:
			if(led == LED_RED){
				HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 0);
				HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, 0);
				HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 1);
				HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, 1);
				HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 1);
				HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, 1);
			}else if(led == LED_AMBER){
				HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 1);
				HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, 1);
				HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 0);
				HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, 0);
				HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 1);
				HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, 1);
			}else{
				HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 1);
				HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, 1);
				HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 1);
				HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, 1);
				HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 0);
				HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, 0);
			}
			if(timer_flag[2] == 1){
				currentLed = LED_OFF;
				setTimer(2, duration);
			}
			break;
		case LED_OFF:
			if(led == LED_RED){
				HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, 1);
				HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, 1);
			}else if(led == LED_AMBER){
				HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, 1);
				HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, 1);
			}else{
				HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, 1);
				HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, 1);
			}
			if(timer_flag[2] == 1){
				currentLed = LED_ON;
				setTimer(2, duration);
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
			setTime7SEG1(durationLedRed);
			handleTime1();
			setTimer(4, 1000);

			status = AUTO_LED_RED;
			break;
		case AUTO_LED_RED:
			onLedRed1();
			if(timer_flag[0] == 1){
				status = AUTO_LED_GREEN;
				setTimer(0, durationLedGreen*1000);
				setTime7SEG1(durationLedGreen);
				handleTime1();
				setTimer(4, 1000);
			}
			break;
		case AUTO_LED_GREEN:
			onLedGreen1();
			if(timer_flag[0] == 1){
				status = AUTO_LED_AMBER;
				setTimer(0, durationLedAmber*1000);
				setTime7SEG1(durationLedAmber);
				handleTime1();
				setTimer(4, 1000);
			}
			break;
		case AUTO_LED_AMBER:
			onLedAmber1();
			if(timer_flag[0] == 1){
				status = AUTO_LED_RED;
				setTimer(0, durationLedRed*1000);
				setTime7SEG1(durationLedRed);
				handleTime1();
				setTimer(4, 1000);
			}
			break;
		default:
			break;
	}
}

void runTraficLight2(){
	switch (status2){
		case INIT:
			offALL2();
			setTimer(5, durationLedGreen*1000);
			setTime7SEG2(durationLedGreen);
			handleTime2();
			setTimer(6, 1000);

			status2 = AUTO_LED_GREEN;
			break;
		case AUTO_LED_RED:
			onLedRed2();
			if(timer_flag[5] == 1){
				status2 = AUTO_LED_GREEN;
				setTimer(5, durationLedGreen*1000);
				setTime7SEG2(durationLedGreen);
				handleTime2();
				setTimer(6, 1000);
			}
			break;
		case AUTO_LED_GREEN:
			onLedGreen2();
			if(timer_flag[5] == 1){
				status2 = AUTO_LED_AMBER;
				setTimer(5, durationLedAmber*1000);
				setTime7SEG2(durationLedAmber);
				handleTime2();
				setTimer(6, 1000);
			}
			break;
		case AUTO_LED_AMBER:
			onLedAmber2();
			if(timer_flag[5] == 1){
				status2 = AUTO_LED_RED;
				setTimer(5, durationLedRed*1000);
				setTime7SEG2(durationLedRed);
				handleTime2();
				setTimer(6, 1000);
			}
			break;
		default:
			break;
	}
}


