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
int index_led;

extern int seg1_chuc;
extern int seg1_donvi;
extern int seg2_chuc;
extern int seg2_donvi;

void setTime7SEG1(int duration);
void handleTime1();
void update7SEGBuffer1();

void setTime7SEG2(int duration);
void handleTime2();
void update7SEGBuffer2();

void display7SEG(int num);
void update7SEG(int index);
void init7SEG();

void run_seven_segment();

#endif /* INC_SEVEN_SEGMENT_H_ */
