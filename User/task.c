/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main program body
  ******************************************************************************
  * @attention

**/

/* Includes ------------------------------------------------------------------*/
#include "task.h"



const RC_ctrl_t *FS_controller;
float pressure;
int vel1;
int vel2;
int detect;
int8_t stage2 =0;
int8_t stage3 =0;
int8_t stage4 =0;
int8_t stage5 =0;
int8_t stage6 =0;
int8_t stage7 =0;
char s_prev[4];
int8_t led_state = 0;
float yaw_d;

void TASKS_Ctrl(void);
void LED_Init(void);


/** @addtogroup Template_Project
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
void TASKS_Init()
{
	/* Hardware Configuation */
	delayInit(180);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	Remote_Config();


//	adc_pressureConfig();

	FS_controller = get_remote_control_point();
	
	CAN1_Configuration();	
	delay_ms(500);	
	
	LS_Driver1_Enable();
	LS_Driver2_Enable();
	
	
	JY901_usart2_Init(9600);	//braudrate 9600
	ultrasonic_init();	
	
	
	TIM3_Init(999, 83);   // 84M /(1000* 84) = 1000   // 999 83
	TIM6_Init(999, 83);



}


void TASKS_Timer_H_1000hz()
{

}

void TASKS_Timer_H_100hz()
{
	TASKS_Ctrl();
	detect = distance_detect();
	
	if(chassis.update % 10 == 0){
		yaw_d = yaw_stable();
		
	}
}

void TASKS_Timer_H_50hz()
{

}

void TASKS_Timer_H_10hz()
{	
//	pressure = get_ADC_pressure();

}

void TASKS_Timer_H_1hz()
{
	if(led_state == 0){
		GPIO_ResetBits(GPIOF,GPIO_Pin_9);  //LED0对应引脚GPIOF.9拉低，亮  等同LED0=0;
		GPIO_SetBits(GPIOF,GPIO_Pin_10);   //LED1对应引脚GPIOF.10拉高，灭 等同LED1=1;	
		led_state = 1;
	}
	else{		
		GPIO_SetBits(GPIOF,GPIO_Pin_9);	   //LED0对应引脚GPIOF.0拉高，灭  等同LED0=1;
		GPIO_ResetBits(GPIOF,GPIO_Pin_10); //LED1对应引脚GPIOF.10拉低，亮 等同LED1=0;
		led_state = 0;
	}


}

void TASKS_Timer_L_1000hz()
{

}

void TASKS_Timer_L_100hz()
{

}

void TASKS_Timer_L_50hz()
{

}


void TASKS_Timer_L_10hz()
{
}

void TASKS_Timer_L_1hz()
{
}


void TASKS_Ctrl(void){	
	vel1 = map(FS_controller->rc.ch[1],-784,783,-3000,3000);
	vel2 = map(FS_controller->rc.ch[2],-784,783,-3000,3000);		
	if(FS_controller->sw.swA == RC_SW_UP  && FS_controller->sw.swD != RC_SW_DOWN ){
		stage2=0;
		stage3=0;
		stage4=0;
		stage5=0;
		stage6=0;
		stage7=0;		
		LS_Driver1_Set_Rpm(-vel1); 
		LS_Driver2_Set_Rpm(vel2);		
	}
	else if(FS_controller->sw.swD == RC_SW_DOWN){
		if(s_prev[3] != RC_SW_DOWN){
			chassis.set_yaw = chassis.yaw;
			chassis_set_pos(4.0);
		}
		
		if(stage2 == 0 && distance_detect() == 0){
			if(chassis_forward() == 1){
				stage2 = 1;	
			}		
		}
		else{
			chassis_set_target_vel(0,0);
			chassis_vel_to_rpm();
			chassis_drive();				
		
		}
		
		
//		
//		
//		if(stage2 == 0 && distance_detect() == 0){
//			if(chassis_forward() == 1){
//				stage2 = 1;	
//				chassis_set_left(180);
//			}			
//		}
//		else if(stage2){
//			if(stage3 == 0 && distance_detect() == 0){
//				if(chassis_turn_left() == 1){				
//					if(yaw_d < 0.05f){
//						stage3 = 1;	
//						chassis_set_pos(5.14);
//						chassis.set_yaw = chassis.yaw;						
//					
//					}
//				
//				}
//			}
//			else if(!stage4 && stage3 && distance_detect() == 0){
//				if(chassis_forward() == 1){
//					stage4 = 1;
//					chassis_set_right(180);
//				}
//			}
//			else if(!stage5 && stage4 && distance_detect() == 0){
//				if(chassis_turn_right() == 1){
//					if(yaw_d < 0.05f){
//						stage5 = 1;	
//						chassis_set_pos(5.14);
//						chassis.set_yaw = chassis.yaw;
//					}
//				
//				}				
//			}
//			else if(!stage6 && stage5 && distance_detect() == 0){
//				if(chassis_forward()==1){
//					stage6 = 1;
//					chassis_set_left(180);
//				}
//			}
//			else if(!stage7 && stage6 && distance_detect() == 0){
//					if(chassis_turn_left() == 1){
//						if(yaw_d < 0.05f){
//							stage7 = 1;	
//							chassis_set_pos(5.14); 
//							chassis.set_yaw = chassis.yaw;							
//						}

//					}
//			}		
//			else if(stage7 && distance_detect() == 0){
//				if(chassis_forward() == 1){
//				}
//			}
//			else{
//				chassis_set_target_vel(0,0);
//				chassis_vel_to_rpm();
//				chassis_drive();
//			}
//		}
//		else{
//			chassis_set_target_vel(0,0);
//			chassis_vel_to_rpm();
//			chassis_drive();		
//		}
	}
	else{				
		LS_Driver1_Set_Rpm(-vel1);
		LS_Driver2_Set_Rpm(vel1);		
		stage2=0;
		stage3=0;
		stage4=0;
		stage5=0;
		stage6=0;
		stage7=0;
	}	
		
	s_prev[0] = FS_controller->sw.swA;
	s_prev[1] = FS_controller->sw.swB;
	s_prev[2] = FS_controller->sw.swC;
	s_prev[3] = FS_controller->sw.swD;
	
}

void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟

  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;//LED0和LED1对应IO口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//GPIOF9,F10设置高，灯灭

}

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
