/*
 * fsm_manual.c
 *
 *  Created on: Nov 27, 2024
 *      Author: DELL
 */


/*
 * fsm.manual.c
 *
 * Created on: Oct 31, 2024
 * Author: DELL
 */

#include "fsm_manual.h"

void fsm_manual_run() {
	switch (state) {
    case RED_MODE:
		number1 = 2;
		number2 = durForRed;
		if (isButtonPressed(MODE_BUTTON) == 1) {
			state = YELLOW_MODE;
		} else if (isButtonPressed(ADD_BUTTON) == 1) {
			durForRed++;
			durForGreen++;
		} else if (isButtonPressed(RESET_BUTTON) == 1) {
			if (durForRed > 2)
				durForRed--;
		} else if (isButtonPressed(CONFIRM_BUTTON) == 1) {
			state = INIT;
		}
		break;
	case YELLOW_MODE:
		number1 = 3;
		number2 = durForRed - durForGreen;
		if (isButtonPressed(MODE_BUTTON) == 1) {
			state = GREEN_MODE;
		} else if (isButtonPressed(ADD_BUTTON) == 1) {
			durForRed++;
		} else if (isButtonPressed(RESET_BUTTON) == 1) {
			if (durForRed - durForGreen > 1) {
				durForRed--;
			}
		} else if (isButtonPressed(CONFIRM_BUTTON) == 1) {
			state = INIT;
		}
		break;
	case GREEN_MODE:
		number1 = 4;
		number2 = durForGreen;
		if (isButtonPressed(MODE_BUTTON) == 1) {
			state = INIT;
		} else if (isButtonPressed(ADD_BUTTON) == 1) {
			durForRed++;
			durForGreen++;
		} else if (isButtonPressed(RESET_BUTTON) == 1) {
			if (durForGreen > 1)
				durForGreen--;
		} else if (isButtonPressed(CONFIRM_BUTTON) == 1) {
			state = INIT;
		}
		break;
	default:
		break;
	}
}
