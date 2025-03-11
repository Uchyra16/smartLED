/*
 * led_control.c
 *
 *  Created on: Mar 9, 2025
 *      Author: domin
 */
#include "led_control.h"
#include "spi.h"

const uint32_t buffer_size = 40+NUMBER_OF_LEDS*24+1;

//Array contains info about all of the available LED units
led_color_t led_array[NUMBER_OF_LEDS];
uint8_t buffer[40+NUMBER_OF_LEDS*24+1] = {0};

void led_init(SPI_HandleTypeDef* spi_handler)
{
	HAL_SPI_Init(&hspi1);
	for(int i = 40; i < 40+NUMBER_OF_LEDS*24+1; i++)
	{
		buffer[i] = ZERO;
	}
}


void led_setDiodeColor(int16_t diode_id, led_color_t color)
{
	if(diode_id >= NUMBER_OF_LEDS-1 || diode_id < 0) return;
	led_array[diode_id] = color;

	for(int i = 40+24*diode_id; i < 40+24*diode_id+24; i++)
	{
		buffer[i] = ZERO;
	}

	if(color.green == 1)
	{
		buffer[40+24*diode_id] = ONE;
		buffer[48+24*diode_id] = ZERO;
		buffer[56+24*diode_id] = ZERO;
	}
	else if(color.red == 1)
	{
		buffer[40+24*diode_id] = ZERO;
		buffer[48+24*diode_id] = ONE;
		buffer[56+24*diode_id] = ZERO;
	}
	else if(color.blue == 1)
	{
		buffer[40+24*diode_id] = ZERO;
		buffer[48+24*diode_id] = ZERO;
		buffer[56+24*diode_id] = ONE;
	}




}

void led_update()
{
	HAL_SPI_Transmit(&hspi1, &buffer, sizeof(buffer), 1000);
}
