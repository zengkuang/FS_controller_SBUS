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

	TIM3_Init(1000, 90);

	TIM6_Init(1000, 90);
	
	FS_controller = get_remote_control_point();
	//DevicePower_Config();

//	CAN1_Config(CAN_SJW_1tq, CAN_BS2_2tq, CAN_BS1_6tq, 5, CAN_Mode_Normal);
//	//CAN2_Config(CAN_SJW_1tq, CAN_BS2_2tq, CAN_BS1_6tq, 5, CAN_Mode_Normal);

//	Switch_Init();

//	TIM3_Init(1000, 90);

//	TIM6_Init(1000, 90);

//	PWM_TIM4_Config();

//	USART6_Init();


}


void TASKS_Timer_H_1000hz()
{

}

void TASKS_Timer_H_100hz()
{

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
