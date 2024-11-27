#include "button.h"

int keyReg0[4] = { NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE };
int keyReg1[4] = { NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE };
int keyReg2[4] = { NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE };
int keyReg3[4] = { NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE };
int button_flag[4] = { 0, 0, 0, 0 };
int timeForPress[4] = { 300, 300, 300, 300 };

int isButtonPressed(int index) {
	if (button_flag[index] == 1) {
		button_flag[0] = 0;
		button_flag[1] = 0;
		button_flag[2] = 0;
		button_flag[3] = 0;
		return 1;
	} else
		return 0;
}

void subKeyProcess(int index) {
	button_flag[index] = 1;
}

void getInputKey() {
	for (int i = 0; i < 4; i++) {
		keyReg0[i] = keyReg1[i];
		keyReg1[i] = keyReg2[i];
		switch (i) {
		case MODE_BUTTON:
			keyReg2[i] = HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin);
			break;
		case ADD_BUTTON:
			keyReg2[i] = HAL_GPIO_ReadPin(ADD_GPIO_Port, ADD_Pin);
			break;
		case RESET_BUTTON:
			keyReg2[i] = HAL_GPIO_ReadPin(RESET_GPIO_Port, RESET_Pin);
			break;
		case CONFIRM_BUTTON:
			keyReg2[i] = HAL_GPIO_ReadPin(CONFIRM_GPIO_Port, CONFIRM_Pin);
			break;
		default:
			break;
		}

		if ((keyReg0[i] == keyReg1[i]) && (keyReg1[i] == keyReg2[i])) {
			if (keyReg2[i] != keyReg3[i]) {
				keyReg3[i] = keyReg2[i];
				if (keyReg2[i] == PRESSED_STATE) {
					subKeyProcess(i);
					timeForPress[i] = 300;
				}
			} else {
				timeForPress[i]--;
				if (timeForPress[i] == 0) {
					timeForPress[i] = 300;
				}
			}
		}
	}
}
