/*
 * seven_segment.c
 *
 *  Created on: Oct 17, 2024
 *      Author: phan thanh huy
 */

#include "seven_segment.h"
#include "trafic_light.h"

GPIO_TypeDef* led7SEG_GPIO_Ports[7] = {
	SEG0_GPIO_Port, SEG1_GPIO_Port, SEG2_GPIO_Port, SEG3_GPIO_Port,
	SEG4_GPIO_Port, SEG5_GPIO_Port, SEG6_GPIO_Port
};

uint16_t led7SEG_Pins[7] = {
	SEG0_Pin, SEG1_Pin, SEG2_Pin, SEG3_Pin,
	SEG4_Pin, SEG5_Pin, SEG6_Pin
};

bool numLed7SEG[10][7] = {{0,0,0,0,0,0,1},
						  {1,0,0,1,1,1,1},
						  {0,0,1,0,0,1,0},
						  {0,0,0,0,1,1,0},
						  {1,0,0,1,1,0,0},
						  {0,1,0,0,1,0,0},
						  {0,1,0,0,0,0,0},
						  {0,0,0,1,1,1,1},
						  {0,0,0,0,0,0,0},
						  {0,0,0,0,1,0,0}
						};

void display7SEG(int num){
	if(num < 0 && num >= 10) return;
	for(int i = 0; i < 7; i++){
		HAL_GPIO_WritePin(led7SEG_GPIO_Ports[i], led7SEG_Pins[i], numLed7SEG[num][i]);
	}
}

void init7SEG(){
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
}

const int MAX_LED;
int index_led = 0;
int led_buffer[4] = { 0, 0, 0, 0};

// Handle tracfic light 1
int seg1_chuc;
int seg1_donvi;

void setTime7SEG1(int duration){
	seg1_chuc = duration/10;
	seg1_donvi = duration%10;
}

void update7SEGBuffer1(){
	led_buffer[0] = seg1_chuc;
	led_buffer[1] = seg1_donvi;
}

void handleTime1(){
	update7SEGBuffer1();
	if(seg1_donvi > 0){
		seg1_donvi--;
	}
	if(seg1_donvi <= 0){
		if(seg1_chuc > 0){
			seg1_chuc--;
			seg1_donvi = 9;
		}
	}
}


// Handle tracfic light 2
int seg2_chuc;
int seg2_donvi;

void setTime7SEG2(int duration){
	seg2_chuc = duration/10;
	seg2_donvi = duration%10;
}

void update7SEGBuffer2(){
	led_buffer[2] = seg2_chuc;
	led_buffer[3] = seg2_donvi;
}

void handleTime2(){
	update7SEGBuffer2();
	if(seg2_donvi > 0){
		seg2_donvi--;
	}
	if(seg2_donvi <= 0){
		if(seg2_chuc > 0){
			seg2_chuc--;
			seg2_donvi = 9;
		}
	}
}


// Handle common
void update7SEG(int index){
	switch (index){
		case 0:
			display7SEG(led_buffer[0]);
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
			break;
		case 1:
			display7SEG(led_buffer[1]);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			break;
		case 2:
			display7SEG(led_buffer[2]);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			break;
		case 3:
			display7SEG(led_buffer[3]);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			break;
		default:
			break;
	}
}


void run_seven_segment(){
	if(index_led > 3){
		index_led = 0;
	}
	update7SEG(index_led++);
}


