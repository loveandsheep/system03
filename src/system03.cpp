//  system03.h
//  agileEyeTest

//  Created by Ovis aries on 2015/05/31.

#include "system03.h"

system03::system03()
{
	
}

void system03::init()
{
	eyes.setup();
	
	motor.setup(true, 3);
	motor.resetDevice();
	motor.resetDevice();
	motor.resetDevice();
	
	motor.enableAllMotor();
	motor.sendSignal(RPI_L6470_SIG_ABSPOS, 0);
	motor.sendSignal(RPI_L6470_SIG_GOTO, 0);
	motor.sendSignal(RPI_L6470_SIG_ACCEL, 0x5);
	motor.sendSignal(RPI_L6470_SIG_ACCEL, 0x5);
	motor.sendSignal(RPI_L6470_SIG_STEPMODE, 7);
	
	goDefault = true;
	motor_pos.assign(3, 0);
}

void system03::update(const ofVec3f target)
{
	
	eyes.update(target);
	
	if (goDefault){//初期位置
		sendDefaultPos();
	}else{
		motor.enableAllMotor();
		motor_pos[0] = -eyes.arm[0].rootPan / 1.8f;//1.8何？
		motor_pos[1] = -eyes.arm[1].rootPan / 1.8f;
		motor_pos[2] = -eyes.arm[2].rootPan / 1.8f;
		motor.setGo_toMult(motor_pos);
	}
}

void system03::view()
{
	eyes.draw();
	if (goDefault) ofDrawBitmapString("set default position", 80, 80);
}

void system03::sendDefaultPos()
{
	motor.enableAllMotor();
	motor_pos[0] = 0;
	motor_pos[1] = 0;
	motor_pos[2] = 0;
	motor.setGo_toMult(motor_pos);
}

system03::~system03()
{

}