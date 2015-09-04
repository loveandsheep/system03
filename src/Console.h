//
//  Console.h
//  system03
//
//  Created by Ovis aries on 2015/08/31.
//
//

#ifndef __system03__Console__
#define __system03__Console__

#include "ofMain.h"
#include "system03.h"
#include "Pointer.h"

#include "ofxObjLoader.h"

class Console{
public:
	void init();
	void update();
	void view();
	
	/* Section */
	void drawUnit();
	void drawAnglePattern();
	void drawMotorGraph();
	void drawPatternUnit();

	/* Modules */
	void drawCode(float v);
	void drawMotorAngle(float angle);
	
	ofFbo buffer;
	
	ofEasyCam camera;
	Pointer *pointPtr;
	system03 *sysPtr;
	
	float motor_smooth[3];
	ofVec3f currentTarg_smooth;
	
	deque<float> motorlog[3];
	
	ofNode unitNode;
	ofNode unitLinkNode[3];
	ofMesh unitMesh;
	
	ofQuaternion sphericalLinear(ofQuaternion q1,
								 ofQuaternion q2,
								 float t);
	
	ofFloatColor themeColor;
};

#endif /* defined(__system03__Console__) */
