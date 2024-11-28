/*
 * fsm_automic.h
 *
 *  Created on: Nov 19, 2024
 *      Author: phan thanh huy
 */

#ifndef INC_FSM_AUTOMATIC_H_
#define INC_FSM_AUTOMATIC_H_

#include "global.h"

typedef enum {
    LED_ON,
	LED_OFF
} LedStateToggle;

typedef enum {
    LED_RED,
	LED_AMBER,
	LED_GREEN
} ledType;

extern int durationLedRed;
extern int durationLedAmber;
extern int durationLedGreen;

void onLedRed1();
void onLedAmber1();
void onLedGreen1();
void onLedRed2();
void onLedAmber2();
void onLedGreen2();
void offALL1();
void offALL2();

void togglelLed(int duration, ledType led); // duration giua cac led voi nhau

void fsm_automatic1();
void fsm_automatic2();

#endif /* INC_FSM_AUTOMATIC_H_ */
