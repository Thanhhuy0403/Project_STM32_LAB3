/*
 * global.h
 *
 *  Created on: Oct 19, 2024
 *      Author: phan thanh huy
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "software_timer.h"
#include "stdbool.h"
#include "trafic_light.h"
#include "button.h"
#include "seven_segment.h"

#define INIT				0
#define AUTO_LED_RED		1
#define AUTO_LED_AMBER		2
#define AUTO_LED_GREEN		3

#define MODE_1 				10
#define MODE_2				11
#define MODE_3				12

/*
 * timer_flag[0]: trafic_light 1
 * timer_flag[1]: button mode
 * timer_flag[2]: toggle led
 * timer_flag[3]: display 7SEG
 * timer_flag[4]: handle time 7SEG
 * timer_flag[5]: trafic_light 2
 * */

extern int status;
extern int status2;

#endif /* INC_GLOBAL_H_ */
