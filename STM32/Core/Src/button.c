/*
 * button.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Acer
 */
#include "button.h"

//we aim to work with more than one buttons
#define N0_OF_BUTTONS 				       3
//timer interrupt duration is 10ms, so to pass 1 second,
//we need to jump to the interrupt service routine 100 time
#define DURATION_FOR_AUTO_INCREASING	100
#define BUTTON_IS_PRESSED   GPIO_PIN_RESET
#define BUTTON_IS_RELEASED   GPIO_PIN_SET
#define BUTTON_PRESSED_MORE_THAN_1s	2

#define BUTTON_PRESSED GPIO_PIN_RESET // 0
#define BUTTON_RELEASED GPIO_PIN_SET  // 1
//the buffer that the final result is stored after
//debouncing
static GPIO_PinState buttonBuffer[N0_OF_BUTTONS];
//we define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer3[N0_OF_BUTTONS];
//we define a flag for a button pressed more than 1 second.
static uint8_t flagForButtonPress1s[N0_OF_BUTTONS];
//we define counter for automatically increasing the value
//after the button is pressed more than 1 second.
static uint16_t counterForButtonPress1s[N0_OF_BUTTONS];
static int buttonState[N0_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
static int button_flag[N0_OF_BUTTONS];
void getKeyProcess(int index){// turn on button_flag
	if(index >= 0 && index < N0_OF_BUTTONS){
		button_flag[index] = 1;
	}
}
void get1sFlag(int index){
	if(index >= 0 && index < N0_OF_BUTTONS){
			flagForButtonPress1s[index] = 1;
		}
}
void fsm_input_processing(int index){
	switch(buttonState[index]){
	case BUTTON_IS_RELEASED:
		//button is pressed
		if(buttonBuffer[index] == BUTTON_PRESSED){
			buttonState[index] = BUTTON_IS_PRESSED;
			getKeyProcess(index);
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1s:
		if(counterForButtonPress1s[index] < DURATION_FOR_AUTO_INCREASING*3){
					counterForButtonPress1s[index]++;
					if(counterForButtonPress1s[index] == DURATION_FOR_AUTO_INCREASING*3){
						buttonState[index] = BUTTON_PRESSED_MORE_THAN_1s;
						counterForButtonPress1s[index] = 0;
//						getKeyProcess(index);
//						get1sFlag(index);
						flagForButtonPress1s[index] = 0;
					}
				}
		if(buttonBuffer[index] == BUTTON_RELEASED){
			buttonState[index] = BUTTON_IS_RELEASED;
			counterForButtonPress1s[index] = 0;
			flagForButtonPress1s[index] = 0;
		}
		break;
	case BUTTON_IS_PRESSED:
		//if button is pressed more than 1s
		if(counterForButtonPress1s[index] < DURATION_FOR_AUTO_INCREASING){
			counterForButtonPress1s[index]++;
			if(counterForButtonPress1s[index] == DURATION_FOR_AUTO_INCREASING){
				counterForButtonPress1s[index] = 0;
				getKeyProcess(index);
				get1sFlag(index);
				buttonState[index] = BUTTON_PRESSED_MORE_THAN_1s;
			}
		}
		// button is release
		if(buttonBuffer[index] == BUTTON_RELEASED){
			buttonState[index] = BUTTON_IS_RELEASED;
			counterForButtonPress1s[index] = 0;
		}
		break;
	default:
		break;
	}
}
void button_reading(void){
	for(uint8_t i = 0; i < N0_OF_BUTTONS; i++){
		debounceButtonBuffer3[i] = debounceButtonBuffer2[i];
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		// Chosing Which button is pressed.
		switch(i){
		case 0: // read signal from button0
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON_0_GPIO_Port, BUTTON_0_Pin);
			break;
		case 1://  read signal from button1
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
			break;
		case 2://  read signal from button2
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
			break;
		default:
			break;
		}
		if((debounceButtonBuffer3[i] == debounceButtonBuffer2[i]) && (debounceButtonBuffer2[i] == debounceButtonBuffer1[i])){
			buttonBuffer[i] = debounceButtonBuffer3[i];
			// call back fsm_input_processing to
			fsm_input_processing(i);
		}

	}
}
int is_button_pressed(uint8_t index){
	if(index >= N0_OF_BUTTONS) return 0;
	if(button_flag[index] == 1){
		//set button flag value = 0
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}

int  is_button_pressed_1s(uint8_t index){
	if(index >= N0_OF_BUTTONS) return 0;
	if( flagForButtonPress1s[index] == 1 ){
		//set button value
//		button_flag[index] = 0;
//		button_flag[index] = 1;
//		flagForButtonPress1s[index] = 1;
		return 1;
	}
	return 0;
}
