/*
 * trafic_light.h
 *
 *  Created on: Oct 19, 2024
 *      Author: phan thanh huy
 */

#ifndef INC_TRAFIC_LIGHT_H_
#define INC_TRAFIC_LIGHT_H_

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

void runTraficLight1();
void runTraficLight2();

#endif /* INC_TRAFIC_LIGHT_H_ */
