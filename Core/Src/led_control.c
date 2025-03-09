/*
 * led_control.c
 *
 *  Created on: Mar 9, 2025
 *      Author: domin
 */
#include <led_control.h>
#include "tim.h"

void led_init()
{
	  /*************TIMER CONFIG***************/
	  /*
	   * 	MCU frequency - 80 MHz
	   * 	LED communication: 1 bit is 1,25 us
	   * 	80 MHz = 80 000 000 Hz = 80 1/us
	   * 	80 - us
	   * 	x - 1,25 us
	   * 	x = 100
	   * 	100 clock cycles is the time length of one bit for WS2812B LED's
	   *
	   */
	  HAL_TIM_Base_Start(&htim3);

	  /************LED CONTROL*****************/
	  /*
	   * 	40 * 1,25 us = 50 us -> RESET //ZWIEKSZAM DLUGOSC RESETU
	   * 	8 LEDS on strip, GRB colors each 8 bits -> 8 * 24
	   * 	After sending data we want the signal to be HIGH -> + 1
	   * 	Setting duty to 32 -> off
	   * 	Setting duty to 64 -> on
	  */
	  uint8_t test[45 + 7 * 24 + 1] = {0};

	  for (int i = 0; i < 7 * 24; i++)
	    test[45 + i] = 64;

	  //HIGH signal at the end
	  test[45 + 7 * 24] = 100;

	  //DMA dynamically updates PWM duty
	  HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, &test, sizeof(test));
	  HAL_Delay(1000);

	  for (int i = 0; i < 7 * 24; i++)
	    test[45 + i] = 32;
	  HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, &test, sizeof(test));



}

