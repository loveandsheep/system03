//  system03.h
//  agileEyeTest

//  Created by Ovis aries on 2015/05/31.

#ifndef __agileEyeTest__system03__
#define __agileEyeTest__system03__

#include "ofMain.h"
#include "ofxKsmrRPiToL6470.h"
#include "ofxKsmrAgileEye.h"

#define LASER_PIN	17
#define LIGHT_PIN	21
#define DEFAULT_PIN	26

class system03{
	
public:
	system03();
	~system03();
	
	void				init();
	void				update(const ofVec3f target);
	void				view();
	
	void				sendDefaultPos();
	void				setLaser(bool b);
	
	ofxKsmrAgileEye		eyes;
	ofxKsmrRPiToL6470	motor;
	
	vector<int>			motor_pos_prev;
	vector<int>			motor_pos;
	
	int					base_accel;
	int					base_decel;
	int					base_speed;
	int					maxMove;
	
	bool				goDefault;
	bool				laserState;
	
	bool				defaultPinPrev;
	bool				defaultPinValue;
	
	static const int center = 12800;
};

#endif /* defined(__agileEyeTest__system03__) */
