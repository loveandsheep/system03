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
	
#ifndef TARGET_OSX
	pinMode(LASER_PIN, OUTPUT);
	pinMode(LIGHT_PIN, OUTPUT);
	pinMode(DEFAULT_PIN, INPUT);
	pullUpDnControl(DEFAULT_PIN, PUD_UP);
	digitalWrite(LASER_PIN, true);
	digitalWrite(LIGHT_PIN, true);
#endif
	
	sleep(1);
	motor.enableAllMotor();
	motor.sendSignal(RPI_L6470_SIG_ACCEL, 0x10);
	motor.sendSignal(RPI_L6470_SIG_DECEL, 0x10);
	motor.sendSignal(RPI_L6470_SIG_MAXSPEED, 0x40);
	motor.sendSignal(RPI_L6470_SIG_MINSPEED, 0x0);
	motor.sendSignal(RPI_L6470_SIG_VOLT_RUN, 0x80);
	motor.sendSignal(RPI_L6470_SIG_VOLT_ACC, 0x80);
	motor.sendSignal(RPI_L6470_SIG_VOLT_DEC, 0x80);
	motor.sendSignal(RPI_L6470_SIG_VOLT_HOLD, 0x80);
	motor.sendSignal(RPI_L6470_SIG_ABSPOS, center);
	motor.sendSignal(RPI_L6470_SIG_GOTO, center);
	motor.sendSignal(RPI_L6470_SIG_STOP_HARD, 0);
	motor.sendSignal(RPI_L6470_SIG_STEPMODE, 7);
	
	goDefault = false;
	motor_pos.assign(3, 0);
	motor_pos_prev.assign(3, 0);
	
	base_accel = 20;
	base_decel = 20;
	base_speed = 80;
	maxMove = 45;
	
	defaultPinValue = true;
}

void system03::update()
{
#ifndef TARGET_OSX
	defaultPinValue = digitalRead(DEFAULT_PIN);
#endif
	
	if ((!defaultPinValue) && (defaultPinPrev))
	{
		cout << "Toggle" << goDefault << endl;
		goDefault ^= true;
	}
	defaultPinPrev = defaultPinValue;
}

void system03::updateTarg(const ofVec3f target)
{
	
	eyes.update(target);
	
	if (goDefault){//初期位置
		sendDefaultPos();
	}else{
		for (int i = 0;i < int(motor_pos.size());i++)
			motor_pos_prev[i] = motor_pos[i];
		
		motor_pos[0] = -eyes.arm[1].rootPan / 1.8f * 128 + center;
		motor_pos[1] = -eyes.arm[2].rootPan / 1.8f * 128 + center;
		motor_pos[2] = -eyes.arm[0].rootPan / 1.8f * 128 + center;
		
		//移動量に応じて速度を調整
//		for (int i = 0;i < motor_pos.size();i++)
//		{
//			int spd = abs(motor_pos[i] - motor_pos_prev[i]);
//			float pct = spd / float(maxMove);
//			
//			motor.enableMotor(i);
//			motor.sendSignal(RPI_L6470_SIG_ACCEL, base_accel * pct + 1);
//			motor.sendSignal(RPI_L6470_SIG_DECEL, base_decel * pct + 1);
//			motor.sendSignal(RPI_L6470_SIG_MAXSPEED, base_speed * pct + 1);
//			motor.disableMotor(i);
//		}

		motor.enableAllMotor();
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
	motor_pos[0] = center;
	motor_pos[1] = center;
	motor_pos[2] = center;
	motor.setGo_toMult(motor_pos);
}

void system03::setLaser(bool b)
{
#ifndef TARGET_OSX
	digitalWrite(LASER_PIN, b);
#endif
	laserState = b;
}

system03::~system03()
{

}