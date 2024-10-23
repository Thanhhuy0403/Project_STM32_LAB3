/*
 * Button.h
 *
 *  Created on: Oct 16, 2024
 *      Author: phan thanh huy
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "software_timer.h"
#include "main.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

extern int button_flag[3];
int isButtonPressed(int index);
void initButton();
void getKeyInput();

void run_handleMode();

#endif /* INC_BUTTON_H_ */
