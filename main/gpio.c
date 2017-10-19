/******************************************************************************
 * 
 * Copyright 2017 karawin (http://www.karawin.fr)
 *
*******************************************************************************/


#include "driver/gpio.h"
#include "gpio.h"


void gpio_output_conf(gpio_num_t gpio)
{
	gpio_config_t gpio_conf;
	gpio_conf.pin_bit_mask =(BIT(gpio)) ;
	gpio_conf.mode = GPIO_MODE_OUTPUT;
	gpio_conf.pull_up_en =  GPIO_PULLUP_DISABLE;
	gpio_conf.pull_down_en =  GPIO_PULLDOWN_DISABLE;
	gpio_conf.intr_type = GPIO_INTR_DISABLE;
	gpio_config(&gpio_conf);
	gpio_set_level(gpio,1);
}

