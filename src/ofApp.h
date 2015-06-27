#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "system03.h"
#include "fontPointer.h"
#include "ofxKsmrRPiToL6470.h"

#define LASER_PIN 17

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	
	void exit();

	ofEasyCam		camera;
	system03		sys03;
	fontPointer		fontPt;
	ofxOscReceiver	receiver;

};
