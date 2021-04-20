/*
 * NB_HAL_STEPPER_DRIVER.h
 *
 *  Created on: Apr 19, 2021
 *      Author: Chevrier-Chahidi Arthur
 */
#include "stm32f407xx.h"
#include "main.h"

#ifndef INC_NB_HAL_STEPPER_DRIVER_H_
#define INC_NB_HAL_STEPPER_DRIVER_H_

#define STEPS_FULL_DRIVE 2048
#define STEPS_WAVE_DRIVE 2048
#define STEPS_HALF_DRIVE 4096
#define CLOCKWISE 0
#define ANTICLOCKWISE 1

/*---------------------------------GPIO CONFIGUARTION---------------------------------------------------------*/

/* You only need to change the define of the GPIO configuration if you need to change the PIN for your motor  */
#define IN1_RESET HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET)
#define IN1_SET HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET)

#define IN2_RESET HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET)
#define IN2_SET HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET)

#define IN3_RESET HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET)
#define IN3_SET HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET)

#define IN4_RESET HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define IN4_SET HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

/*-------------------------------------------------------------------------------------------------------------*/

void stepper_full_drive (uint16_t step);
void stepper_half_drive (uint16_t step);
void stepper_wave_drive (uint16_t step);
void stepper_set_rpm (uint8_t rpm);
void stepper_reset_gpio(void);
uint8_t stepper_step_angle (float angle, uint8_t direction);

#endif /* INC_NB_HAL_STEPPER_DRIVER_H_ */
