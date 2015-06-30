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
	
	void				sendDefaultPos();
	
	ofxKsmrAgileEye		eyes;
	ofxKsmrRPiToL6470	motor;
	
	vector<int>			motor_pos;
	bool				goDefault;
	
	static const int center = 12800;
};

#endif /* defined(__agileEyeTest__system03__) */
