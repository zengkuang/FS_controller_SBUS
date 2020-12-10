#include "ultrasonic.h"


void ultrasonic_init(void){
			

 GPIO_InitTypeDef GPIO_InitStructure;

 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
 GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
	
 GPIO_Init(GPIOE, &GPIO_InitStructure);

}


uint8_t distance_detect(void){	
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0) == 1){
		return 1;	
	}
	else{
		return 0;	
	}
}
