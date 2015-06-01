//  system03.h
//  agileEyeTest

//  Created by Ovis aries on 2015/05/31.

#include "system03.h"

void system03::init()
{
	eyes.setup();
	
	goDefault = true;
	
	motor.serial.listDevices();
	motor.addStepper("arm_0", 200, 0);
	motor.addStepper("arm_1", 200, 1);
	motor.addStepper("arm_2", 200, 2);
	motor.setupEasyFromPreset(KSMR_STEP_SM_42BYG011_25);
	motor.setParam_maxSpeed(0x75);
	motor.setMicroSteps(0);
	
}

void system03::update(const ofVec3f target)
{
	
	eyes.update(target);
	
	if (goDefault){
		motor.setStepperAll(true);
		motor_pos[0] = 0;
		motor_pos[1] = 0;
		motor_pos[2] = 0;
		
		motor.multi_go_to(motor_pos);
	}else{
		motor.setStepperAll(true);
		
		motor_pos[0] = -eyes.arm[0].rootPan / 1.8f * 128;
		motor_pos[1] = -eyes.arm[2].rootPan / 1.8f * 128;
		motor_pos[2] = -eyes.arm[1].rootPan / 1.8f * 128;
		
		motor.multi_go_to(motor_pos);
	}
}

void system03::view()
{
	eyes.draw();
}