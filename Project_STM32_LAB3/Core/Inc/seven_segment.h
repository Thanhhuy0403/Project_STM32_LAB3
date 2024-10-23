/*
 * seven_segment.h
 *
 *  Created on: Oct 17, 2024
 *      Author: phan thanh huy
 */

#ifndef INC_SEVEN_SEGMENT_H_
#define INC_SEVEN_SEGMENT_H_

#include "global.h"

extern int led_buffer[4];
extern int index_led;
extern int seg1_chuc;
extern int seg1_donvi;

void display7SEG(int num);
void update7SEG(int index);
void update7SEGBuffer1();
void handleTime1();
void init7SEG();
void setTime7SEG(int duration);
void run_seven_segment();

#endif /* INC_SEVEN_SEGMENT_H_ */
