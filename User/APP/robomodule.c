#include "robomodule.h"

robomodule_t robomodule[2];

void robomodule_SetCur(uint8_t id, int16_t cur){
	robomodule[id].config.set_cur = cur;
}

void robomodule_SetVel(uint8_t id, int16_t vel){
	robomodule[id].config.set_vel = vel;
}

void robomodule_SetPos(uint8_t id, float pos){
	robomodule[id].config.set_pos = pos;
}

void robomodule_SetPwm(uint8_t id, int16_t pwm){
	robomodule[id].config.set_pwm = pwm;
}

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
