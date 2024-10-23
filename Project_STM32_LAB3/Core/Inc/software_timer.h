/*
 * sofeware_timer.h
 *
 *  Created on: Oct 16, 2024
 *      Author: phan thanh huy
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "global.h"
#include "stdbool.h"

int timer_counter[10];
extern bool timer_flag[10];
int TIMER_CYCLE;

void setTimer(int index, int duration);
void runTimer();

#endif /* INC_SOFTWARE_TIMER_H_ */
