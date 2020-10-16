#include "adc.h"

static uint16_t get_ADC(uint8_t ch);
uint32_t temp;
float pres;

void adc_pressureConfig(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef ADC_InitStructure;


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); //ADC1
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//PA5 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);
	
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay =ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInit(&ADC_CommonInitStructure);
	

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;        
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge =ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign= ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	
	ADC_Cmd(ADC1, ENABLE);

}

static uint16_t get_ADC(uint8_t ch)
{

    ADC_ClearFlag(ADC1,ADC_FLAG_STRT|ADC_FLAG_OVR|ADC_FLAG_EOC);
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_15Cycles);

    ADC_SoftwareStartConv(ADC1);

    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    return ADC_GetConversionValue(ADC1);
}

float get_ADC_average(uint8_t ch,uint8_t times)
{

	uint32_t temp_val = 0;
	uint8_t t;
	for(t=0;t<times;t++){
		temp_val = temp_val + get_ADC(ch);
		delay_ms(5);
	}
	
  return temp_val/times;
}

float get_ADC_pressure(void){
	temp = get_ADC(ADC_Channel_5);
	pres = temp * (5.0f/4096.0f);
	
	return pres;
}



