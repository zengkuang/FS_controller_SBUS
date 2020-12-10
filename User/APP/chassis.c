#include "chassis.h"

chassis_info chassis;

void chassis_set_rpm(int16_t left_rpm, int16_t right_rpm){
	chassis.left_rpm = left_rpm;
	chassis.right_rpm = right_rpm;

}

void chassis_set_vel(float left_vel, float right_vel){
	chassis.left_vel = left_vel;
	chassis.right_vel = right_vel;
	
//	chassis.set_left_vel = left_vel;	
//	chassis.set_right_vel = right_vel;
}


void chassis_set_target_vel(float left_vel, float right_vel){
	chassis.set_left_vel = left_vel;
	chassis.set_right_vel = right_vel;
}


void chassis_acc_vel(float left_vel, float right_vel){
	chassis.left_vel += left_vel;
	chassis.right_vel += right_vel;	
}
		
void chassis_vel_to_rpm(void){
	if(chassis.left_vel<chassis.set_left_vel){
			chassis_acc_vel(0.016,0.016);
	}
	else if(chassis.left_vel>chassis.set_left_vel){
			chassis_acc_vel(-0.016,-0.016);	
	}
	else{
			chassis_set_vel(chassis.set_left_vel,chassis.set_right_vel);
	}
	
			
	chassis.left_rpm = (chassis.left_vel / (diameter*3.14f) * 60.0f * reduction_ratio);
	chassis.right_rpm = (chassis.right_vel  / (diameter*3.14f) * 60.0f * reduction_ratio);		
		
	if(chassis.left_rpm > 3000){
		chassis.left_rpm = 3000;
	}
	else if(chassis.left_rpm < -3000){
		chassis.left_rpm = -3000;
	}
	
	if(chassis.right_rpm > 3000){

		
		chassis.right_rpm = 3000;
	}
	else if(chassis.right_rpm < -3000){
		chassis.right_rpm = -3000;
	}	
		
}

void chassis_drive(void){
	LS_Driver1_Set_Rpm(-chassis.left_rpm);
	LS_Driver2_Set_Rpm(chassis.right_rpm);	
}

void chassis_set_pos(float distance){	
	chassis.set_left_pulse = chassis.left_pulse + distance * pulse_per_meter;	
	chassis.set_left_vel = 0.16;
	chassis.set_right_vel = 0.16;
}

int8_t chassis_forward(){
	
	if(chassis.left_pulse < chassis.set_left_pulse){
//		chassis_set_vel(0.16- yaw_difference()*0.02,0.16 );
		if(chassis.left_vel<chassis.set_left_vel){
		}
		else{
			chassis_set_vel(0.16- yaw_difference()*0.02,0.16);
//			chassis_set_vel(0.16,0.16);
		}
		chassis_vel_to_rpm();
		chassis_drive();
		return 0;
	}
	else{
		chassis_set_target_vel(0,0);
		chassis_vel_to_rpm();
		chassis_drive();
		return 1;
	}
}

int8_t yaw_difference(void){
	
	if(chassis.yaw < -145 && chassis.set_yaw > 145){
		return (chassis.yaw + 180 + 180 - chassis.set_yaw );
	
	}
	else if(chassis.yaw > 145 && chassis.set_yaw < -145){
		return (chassis.yaw - 180 - 180- chassis.set_yaw);	
	}
	else{
		return (chassis.yaw - chassis.set_yaw);	
	}


}

float yaw_stable(void){
	return ((chassis.yaw_d[5] + chassis.yaw_d[6] + chassis.yaw_d[7] + chassis.yaw_d[8] + chassis.yaw_d[9]) - (chassis.yaw_d[0] + chassis.yaw_d[1] + chassis.yaw_d[2] + chassis.yaw_d[3] + chassis.yaw_d[4]))/5.0f;
}

void chassis_set_left(int angle){
	chassis.set_yaw = chassis.yaw + angle;
	chassis.set_right_pulse = chassis.right_pulse -  2.82f * pulse_per_meter;
	if(chassis.set_yaw >180){
		chassis.set_yaw = chassis.yaw - 180  ;
	}
}


void chassis_set_right(int angle){
	chassis.set_yaw = chassis.yaw + angle;
	chassis.set_left_pulse = chassis.left_pulse + 2.82f * pulse_per_meter;	
	if(chassis.set_yaw >180){
		chassis.set_yaw = chassis.yaw - 180  ;
	}
}

int8_t chassis_turn_left(void){
//	if(abs(chassis.yaw - chassis.set_yaw ) > 2){
//		chassis_set_vel(0.20,0);
//		chassis_vel_to_rpm();
//		chassis_drive();
//		return 0;	
//	}
//	else{
//		return 1;
//	}
	if(chassis.right_pulse > chassis.set_right_pulse){
		chassis_set_vel(0.16,0);
		chassis_vel_to_rpm();
		chassis_drive();
		return 0;	
	}
	else{
		if(fabs(chassis.yaw - chassis.set_yaw ) > 3){
			chassis_set_vel(0.16,0);
			chassis_vel_to_rpm();
			chassis_drive();
			return 0;					
		}
		else{
			chassis_set_vel(0,0);
			chassis_vel_to_rpm();
			chassis_drive();		
			return 1;			
		
		}

	}

}

int8_t chassis_turn_right(void){
//	if(abs(chassis.yaw - chassis.set_yaw ) > 2){
//		chassis_set_vel(0,0.20);
//		chassis_vel_to_rpm();
//		chassis_drive();
//		return 0;	
//	}
//	else{
//		return 1;
//	}
	if(chassis.left_pulse < chassis.set_left_pulse){
		chassis_set_vel(0,0.16);
		chassis_vel_to_rpm();
		chassis_drive();
		return 0;	
	}
	else{
		if(fabs(chassis.yaw - chassis.set_yaw ) > 3){
			chassis_set_vel(0,0.16);
			chassis_vel_to_rpm();
			chassis_drive();
			return 0;	
		
		}
		else{
			chassis_set_vel(0,0);
			chassis_vel_to_rpm();
			chassis_drive();
			return 1;		
		
		}

	}

}




	
	

