#ifndef ROBOMODULE_H
#define ROBOMODULE_H
#include "main.h"


#define pwm_limit 5000  //refer to manual of robomodule



typedef struct robomodule_info
{
	float pos;
	int16_t vel;
	int16_t cur;
	char online;
	char ctl1;
	char ctl2;
}robomodule_info;

typedef struct robomodule_config
{
	float set_pos;
	int16_t set_vel;  // -32768~32767 rpm
	int16_t set_cur;	//-32768~32767  mA
	int16_t set_pwm;  // -5000~5000
}robomodule_config;

typedef struct robomodule_t
{
	robomodule_info info;
	robomodule_config config;
}robomodule_t;



extern robomodule_t robomodule[2];

void robomodule_SetCur(uint8_t id, int16_t cur);
void robomodule_SetVel(uint8_t id, int16_t vel);
void robomodule_SetPos(uint8_t id, float pos);
float map(float x, float in_min, float in_max, float out_min, float out_max);



#endif
