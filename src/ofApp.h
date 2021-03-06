#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "system03.h"
#include "fontPointer.h"
#include "ofxKsmrRPiToL6470.h"

#include "Pointer.h"
#include "Console.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void oscManage();
	
	void exit();

	ofEasyCam		camera;
	system03		sys03;
	
	bool			manual;
	ofVec3f			targetPoint;
	ofVec3f			previousPoint;
	ofxOscReceiver	receiver;

	Pointer pointer;
	Console console;
};
