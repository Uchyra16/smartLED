/*
 * led_control.h
 *
 *  Created on: Mar 9, 2025
 *      Author: domin
 */

  /*************LED INPUT VOLTAGE**************/
  /*
   * Vdd 6.0~7.0 V
   * HIGH STATE - min 0.7 Vdd
   * LOW STATE - max 0.3 Vdd
   *
   */
#include <stdint.h>
#include "spi.h"

#ifndef INC_LED_CONTROL_H_
#define INC_LED_CONTROL_H_

#define NUMBER_OF_LEDS 8
#define ZERO 0b100000
#define ONE 0b111000

typedef struct {
	uint8_t red, green, blue;
} led_color_t;


void led_init(SPI_HandleTypeDef* spi_handler);

void led_setDiodeColor(int16_t diode_id, led_color_t color);

void led_update();








#endif /* INC_LED_CONTROL_H_ */
