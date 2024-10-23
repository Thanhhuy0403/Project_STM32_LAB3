/*
 * sofeware_timer.c
 *
 *  Created on: Oct 16, 2024
 *      Author: phan thanh huy
 */

#include "software_timer.h"

int timer_counter[10] = {0};
bool timer_flag[10] = {0};
int TIMER_CYCLE = 10;

void setTimer(int index, int duration){
	timer_counter[index] = duration/TIMER_CYCLE;
	timer_flag[index] = 0;
}

void runTimer(){
	for(int i = 0; i < 10; i++){
		if(timer_counter[i] > 0){
			timer_counter[i]--;
			if(timer_counter[i] <= 0){
				timer_flag[i] = 1;
			}
		}
	}
}


