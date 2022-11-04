/*
 * displayLed.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Acer
 */

#include "displayLed.h"
// corresponding hexadecimal from 0 to 9, example 0 is 0x3f,...
uint16_t led_matrix[MAX_MATRIX] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7D, 0x07, 0x7F, 0x6f};
int index_led = 0;
int led_buffer[MAX_BUFF] = {0,0,0,0};
void display7SEG(int number){
	uint16_t bit_var = led_matrix[number];
	//turn on LED which perform number on LED & SEGMENT
	HAL_GPIO_WritePin(GPIOB, bit_var, RESET);
	//turn off LED which perform number on LED & SEGMENT
	HAL_GPIO_WritePin(GPIOB, ~bit_var, SET);
}

//void update7SEG(int index){
//	switch(index){
//	case 0:
//		// Display the first 7 SEG with led_buffer [0]
//		HAL_GPIO_WritePin(GPIOA, EN0_Pin, RESET);
//		HAL_GPIO_WritePin(GPIOA, EN1_Pin | EN2_Pin | EN3_Pin, SET);
//		display7SEG(led_buffer[0]);
//		break;
//	case 1:
//		// Display the second 7 SEG with led_buffer [1]
//		HAL_GPIO_WritePin(GPIOA, EN1_Pin, RESET);
//		HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN2_Pin | EN3_Pin, SET);
//		display7SEG(led_buffer[1]);
//		break;
//	case 2:
//		// Display the third 7 SEG with led_buffer [2]
//		HAL_GPIO_WritePin(GPIOA, EN2_Pin, RESET);
//		HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN1_Pin | EN3_Pin, SET);
//		display7SEG(led_buffer[2]);
//		break;
//	case 3:
//		// Display the forth 7 SEG with led_buffer [3]
//		HAL_GPIO_WritePin(GPIOA, EN3_Pin, RESET);
//		HAL_GPIO_WritePin(GPIOA, EN0_Pin| EN1_Pin | EN2_Pin , SET);
//		display7SEG(led_buffer[3]);
//		break;
//	default:
//		break;
//	}
//}
