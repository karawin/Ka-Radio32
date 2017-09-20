#pragma once

#define GPIO4	4

void gpio4_output_conf(void);
void gpio4_output_set(uint8_t value);
void gpio16_output_conf(void);
void gpio16_output_set(uint8_t value);
void gpio16_input_conf(void);
uint8_t gpio16_input_get(void);

