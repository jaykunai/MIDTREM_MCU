/*
 * timer.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Acer
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "button.h"
#include "main.h"

extern int timer1_flag;
extern int timer2_flag;
extern int timer3_flag;

void setTimer1(int);
void setTimer2(int);
void setTimer3(int);

void timer_run(void);

#endif /* INC_TIMER_H_ */
