#ifndef CHASSIS_H
#define CHASSIS_H
#include "main.h"

#define diameter 0.3f  // meter
#define wheelbase 1.147f // meter
#define track 0.911f // meter
#define reduction_ratio 160 // 1: 160
#define pulse_per_meter 1698514.0f

typedef struct chassis_info
{
	float left_vel;   // m/s   -0.589 ~ 0.589
	float right_vel;
	float set_left_vel;
	float set_right_vel;
	int16_t left_rpm;  // -3000~3000
	int16_t right_rpm;
	int16_t update;	
	long left_pulse;
	long right_pulse;
	long set_left_pulse;
	long set_right_pulse;
	float set_yaw;
	float yaw_d[10];
	float yaw;
	float pitch;
	float roll;

}chassis_info;

extern chassis_info chassis;

void chassis_set_rpm(int16_t left_rpm, int16_t right_rpm);
void chassis_set_vel(float left_vel, float right_vel);
void chassis_acc_vel(float left_vel, float right_vel);
void chassis_vel_to_rpm(void);
void chassis_set_pos(float distance);
int8_t chassis_forward(void );
void chassis_drive(void);
int8_t yaw_difference(void);
float yaw_stable(void);
void chassis_set_left(int );
void chassis_set_right(int );
void chassis_set_target_vel(float left_vel, float right_vel);
int8_t chassis_turn_left(void);
int8_t chassis_turn_right(void);
//typedef struct robomodule_info
//{
//	float pos;
//	int16_t vel;
//	int16_t cur;
//	char online;
//	char ctl1;
//	char ctl2;
//}robomodule_info;

//typedef struct robomodule_config
//{
//	float set_pos;
//	int16_t set_vel;  // -32768~32767 rpm
//	int16_t set_cur;	//-32768~32767  mA
//	int16_t set_pwm;  // -5000~5000
//}robomodule_config;

//typedef struct robomodule_t
//{
//	robomodule_info info;
//	robomodule_config config;
//}robomodule_t;



//extern robomodule_t robomodule[2];

//void robomodule_SetCur(uint8_t id, int16_t cur);
//void robomodule_SetVel(uint8_t id, int16_t vel);
//void robomodule_SetPos(uint8_t id, float pos);
//float map(float x, float in_min, float in_max, float out_min, float out_max);



#endif
