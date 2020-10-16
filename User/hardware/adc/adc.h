#ifndef ADC_H
#define ADC_H
#include "main.h"

void adc_pressureConfig(void);
float get_ADC_average(uint8_t ch, uint8_t times);
float get_ADC_pressure(void);
#endif
