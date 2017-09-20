
#include "driver/gpio.h"
#include "gpio16.h"

//#define PERIPHS_IO_MUX_GPIO2_U          (PERIPHS_IO_MUX + 0x38)
//#define FUNC_GPIO2                          0


void gpio4_output_conf(void)
{
	gpio_config_t gpio_conf;
	gpio_conf.pin_bit_mask = GPIO_SEL_4;
	gpio_conf.mode = GPIO_MODE_OUTPUT;
	gpio_conf.pull_up_en =  GPIO_PULLUP_DISABLE;
	gpio_conf.pull_down_en =  GPIO_PULLDOWN_DISABLE;
	gpio_conf.intr_type = GPIO_INTR_DISABLE;
	gpio_config(&gpio_conf);
	gpio4_output_set(1);
}

void gpio4_output_set(uint8_t value)
{
 gpio_set_level(4,value);
}


void gpio16_output_conf(void)
{
	gpio_config_t gpio_conf;
	gpio_conf.pin_bit_mask = GPIO_SEL_16;
	gpio_conf.mode = GPIO_MODE_OUTPUT;
	gpio_conf.pull_up_en =  GPIO_PULLUP_ENABLE;
	gpio_conf.pull_down_en =  GPIO_PULLDOWN_DISABLE;
	gpio_conf.intr_type = GPIO_INTR_DISABLE;
	gpio_config(&gpio_conf);	
}

void gpio16_output_set(uint8_t value)
{
	gpio_set_level(16,value);
}

void gpio16_input_conf(void)
{

}

uint8_t gpio16_input_get(void)
{
    return 0;
}

