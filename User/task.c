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

	Remote_Config();


	
	FS_controller = get_remote_control_point();
	
	CAN1_Configuration();
  delay_ms(500);                                      //delay
	
  CAN_RoboModule_DRV_Reset(0,0);                      //reset all   
  delay_ms(500);                                      //delay
	
  CAN_RoboModule_DRV_Config(0,1,10,0);               //configuration one feedback per 10ms    100hz
  delay_us(200);                                   //dealy
	
  CAN_RoboModule_DRV_Config(0,2,10,0);               //configuration one feedback per 10ms  100hz
  delay_us(200);                                      //delay
	
	CAN_RoboModule_DRV_Mode_Choice(0,0,Velocity_Mode);  //Select mode: open loop
  delay_ms(500);                                      //delay
	
	
//
	
//	Switch_Init();

//	PWM_TIM4_Config();

//	USART6_Init();
	
	TIM3_Init(999, 83);   // 84M /(1000* 84) = 1000   // 999 83
	TIM6_Init(999, 83);

}


void TASKS_Timer_H_1000hz()
{

}

void TASKS_Timer_H_100hz()
{
	robomodule[0].config.set_vel = map(FS_controller->rc.ch[1],-784,783,-6000,6000);
	robomodule[1].config.set_vel = map(FS_controller->rc.ch[2],-784,783,-6000,6000);
	CAN_RoboModule_DRV_Velocity_Mode(0,1,pwm_limit,robomodule[0].config.set_vel);
	CAN_RoboModule_DRV_Velocity_Mode(0,2,pwm_limit,robomodule[1].config.set_vel);
}

void TASKS_Timer_H_50hz()
{

}

void TASKS_Timer_H_10hz()
{
}

void TASKS_Timer_H_1hz()
{
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




/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
