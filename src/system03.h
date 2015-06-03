//  system03.h
//  agileEyeTest

//  Created by Ovis aries on 2015/05/31.

#ifndef __agileEyeTest__system03__
#define __agileEyeTest__system03__

#include "ofMain.h"
#include "ofxKsmrRPiStepManager.h"
#include "ofxKsmrAgileEye.h"

class system03{
	
public:
	system03();
	~system03();
	
	void				init();
	void				update(const ofVec3f target);
	void				view();
	
	ofxKsmrAgileEye		eyes;
	ofxKsmrStepManager	*motor;
	
	int					motor_pos[3];
	bool				goDefault;
	
};

#endif /* defined(__agileEyeTest__system03__) */
