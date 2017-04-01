#ifndef HAL_H
#define HAL_H

#include <avr/io.h>

#define DISPLAY_PORT PORTA
#define DISPLAY_DDR DDRA
#define DISPLAY_PIN PINA

// attach termopair to ADC
#define TERMOPAIR_PORT
#define TERMOPAIR_DDR

// attach pwm to power output pin
#define POWER_OUT_PORT
#define POWER_OUT_DDR


#endif
