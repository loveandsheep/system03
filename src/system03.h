//  system03.h
//  agileEyeTest

//  Created by Ovis aries on 2015/05/31.

#ifndef __agileEyeTest__system03__
#define __agileEyeTest__system03__

#include "ofMain.h"
#include "ofxKsmrRPiToL6470.h"
#include "ofxKsmrAgileEye.h"

class system03{
	
public:
	system03();
	~system03();
	
	void				init();
	void				update(const ofVec3f target);
	void				view();
	
	ofxKsmrAgileEye		eyes;
	ofxKsmrRPiToL6470	motor;
	
	int					motor_pos[3];
	bool				goDefault;
	
};

#endif /* defined(__agileEyeTest__system03__) */
