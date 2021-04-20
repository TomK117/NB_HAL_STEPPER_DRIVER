/*
 * NB_HAL_STEPPER_DRIVER.c
 *
 *  Created on: Apr 19, 2021
 *      Author: Chevrier-Chahidi Arthur
 */


#include "main.h"
#include "NB_HAL_STEPPER_DRIVER.h"

TIM_HandleTypeDef htim10;

void stepper_half_drive (uint16_t step)
{
	switch (step){
	case 0:
		IN1_SET;
		IN2_RESET;
		IN3_RESET;
		IN4_RESET;
		break;

	case 1:
		IN1_SET;
		IN2_SET;
		IN3_RESET;
		IN4_RESET;
		break;

	case 2:
		IN1_RESET;
		IN2_SET;
		IN3_RESET;
		IN4_RESET;
		break;

	case 3:
		IN1_RESET;
		IN2_SET;
		IN3_SET;
		IN4_RESET;
		break;

	case 4:
		IN1_RESET;
		IN2_RESET;
		IN3_SET;
		IN4_RESET;
		break;

	case 5:
		IN1_RESET;
		IN2_RESET;
		IN3_SET;
		IN4_SET;
		break;

	case 6:
		IN1_RESET;
		IN2_RESET;
		IN3_RESET;
		IN4_SET;
		break;

	case 7:
		IN1_SET;
		IN2_RESET;
		IN3_RESET;
		IN4_SET;
		break;

	}
}

void stepper_full_drive (uint16_t step){
	switch (step){
	case 0 :
		IN1_SET;
		IN2_SET;
		IN3_RESET;
		IN4_RESET;
		break;
	case 1 :
		IN1_RESET;
		IN2_SET;
		IN3_SET;
		IN4_RESET;
		break;
	case 2 :
		IN1_RESET;
		IN2_RESET;
		IN3_SET;
		IN4_SET;
		break;
	case 3 :
		IN1_SET;
		IN2_RESET;
		IN3_RESET;
		IN4_SET;
		break;
	}
}

void stepper_wave_drive (uint16_t step){

	switch (step){
	case 0 :
		IN1_SET;
		IN2_RESET;
		IN3_RESET;
		IN4_RESET;
		break;
	case 1 :
		IN1_RESET;
		IN2_SET;
		IN3_RESET;
		IN4_RESET;
		break;
	case 2 :
		IN1_RESET;
		IN2_RESET;
		IN3_SET;
		IN4_RESET;
		break;
	case 3 :
		IN1_RESET;
		IN2_RESET;
		IN3_RESET;
		IN4_SET;
		break;
	}
}

void stepper_set_rpm (uint8_t rpm)
{
	uint32_t periode;


	if (rpm > 14){
		rpm = 14; //prevent To go farther than max value
	}
	else if (rpm <= 0){
		rpm = 1; //prevent to go lower than minimum value
	}

	periode = (float) 40000000/STEPS_HALF_DRIVE/rpm + 0.5;

	__HAL_TIM_SET_AUTORELOAD(&htim10,periode);
}

void stepper_reset_gpio(void){
	IN1_RESET;
	IN2_RESET;
	IN3_RESET;
	IN4_RESET;
}

uint8_t stepper_step_angle (float angle, uint8_t direction){

	const float anglepersequence = 0.803;  // 360 = 512 sequences
	uint16_t numberofsequences = (uint16_t) ((angle/anglepersequence + 0.5));

	static uint8_t busy = 0;
	static uint16_t seq = 1;
	static uint16_t step;

	static uint16_t total_step = 0;

	if (direction == ANTICLOCKWISE){// for clockwise
		if(busy == 0)step = 7;
		busy = 1;
		stepper_half_drive(step);
		step--;
		total_step++;
		if (step == 0 && seq != 0){
			step = 7;
			seq++;
		}
		if (total_step >= (numberofsequences * 8)){
			busy = 0;
			stepper_reset_gpio();
			return 1;
		}
	}
	else if (direction == CLOCKWISE){
		if(busy == 0)step = 0;
		busy = 1;
		stepper_half_drive(step);
		step++;
		total_step++;
		if (step  == 7 && seq != 0){
			step = 0;
			seq++;
		}
		if (total_step >= (numberofsequences * 8)){
			busy = 0;
			stepper_reset_gpio();
			return 1;
		}
	}

	return 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim == &htim10){
		static uint8_t test = 0;

		if (test == 0){
			test = stepper_step_angle(20, CLOCKWISE);
			//test = stepper_step_angle(90, ANTICLOCKWISE);
		}
	}
}
