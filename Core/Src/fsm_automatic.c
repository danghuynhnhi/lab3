#include "fsm_automatic.h"
#include "led7_segment.h"

void fsm_automatic_run() {
    switch (state) {
        case INIT:
            // Khởi tạo giá trị ban đầu
            number1 = durForRed - 1;
            number2 = durForGreen - 1;

            // Cấu hình đèn: Đèn đỏ và xanh sáng
            HAL_GPIO_WritePin(GPIOA, D1_Pin, RESET);  // Đỏ
            HAL_GPIO_WritePin(GPIOA, D2_Pin | D3_Pin, SET);
            HAL_GPIO_WritePin(GPIOA, D4_Pin | D5_Pin, SET);
            HAL_GPIO_WritePin(GPIOA, D6_Pin, RESET);  // Xanh

            // Khởi động các bộ đếm
            setTimerRed();
            setTimerGreen();
            setOneSecond();

            // Chuyển sang trạng thái East-West
            state = EastWest;
            break;

        case EastWest:
            if (oneSecondFlag() == 1) {
                // Giảm số đếm
                if (number1 > 0) number1--;
                if (number2 > 0) number2--;
                setOneSecond();
            }

            if (greenFlag() == 1) {
                // Chuyển sang đèn xanh
                HAL_GPIO_WritePin(GPIOA, D4_Pin | D6_Pin, SET);  // Tắt đèn xanh cũ
                HAL_GPIO_WritePin(GPIOA, D5_Pin, RESET);        // Bật đèn vàng
                number2 = durForRed - durForGreen - 1;
            }

            if (redFlag() == 1) {
                // Chuyển sang trạng thái North-South
                number1 = durForGreen-1;
                number2 = durForRed-1;

                HAL_GPIO_WritePin(GPIOA, D1_Pin | D2_Pin, SET);  // Tắt đèn đỏ
                HAL_GPIO_WritePin(GPIOA, D3_Pin, RESET);         // Bật đèn xanh
                HAL_GPIO_WritePin(GPIOA, D5_Pin | D6_Pin, SET);  // Tắt đèn vàng
                HAL_GPIO_WritePin(GPIOA, D4_Pin, RESET);         // Bật đèn xanh

                setTimerRed();
                setTimerGreen();
                setOneSecond();
                state = NorthSouth;
            }

            if (isButtonPressed(MODE_BUTTON)) {
                state = RED_MODE;
            }
            break;

        case NorthSouth:
            if (oneSecondFlag() == 1) {
                // Giảm số đếm
                if (number1 > 0) number1--;
                if (number2 > 0) number2--;
                setOneSecond();
            }

            if (greenFlag() == 1) {
                // Chuyển sang đèn vàng
                HAL_GPIO_WritePin(GPIOA, D1_Pin | D3_Pin, SET);  // Tắt đèn xanh
                HAL_GPIO_WritePin(GPIOA, D2_Pin, RESET);         // Bật đèn vàng
                number1 = durForRed - durForGreen - 1;
            }

            if (redFlag() == 1) {
                // Chuyển lại trạng thái East-West
                number1 = durForRed - 1;
                number2 = durForGreen - 1;

                HAL_GPIO_WritePin(GPIOA, D1_Pin, RESET);  // Đỏ
                HAL_GPIO_WritePin(GPIOA, D2_Pin | D3_Pin, SET);
                HAL_GPIO_WritePin(GPIOA, D4_Pin | D5_Pin, SET);
                HAL_GPIO_WritePin(GPIOA, D6_Pin, RESET);  // Xanh

                setTimerRed();
                setTimerGreen();
                setOneSecond();
                state = EastWest;
            }

            if (isButtonPressed(MODE_BUTTON)) {
                state = RED_MODE;
            }
            break;


        default:
            break;
    }
}
