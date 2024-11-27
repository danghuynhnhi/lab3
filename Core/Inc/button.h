/*
 * button.h
 *
 *  Created on: Nov 27, 2024
 *      Author: DELL
 */
#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE 	SET
#define PRESSED_STATE	RESET

#define MODE_BUTTON 	0
#define ADD_BUTTON		1
#define RESET_BUTTON		2
#define CONFIRM_BUTTON	3

int isButtonPressed(int index);

void subkeyProcess(int index);

void getInputKey();

#endif /* INC_BUTTON_H_ */
