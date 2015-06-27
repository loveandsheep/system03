#pragma once

#include "ofMain.h"
#include "fontPointer.h"
#include "system03.h"

#include "ofxKsmrRPiToL6470.h"
#define LASER_PIN 17

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	ofEasyCam camera;
	fontPointer fontPt;
	system03 sys03;
	
	
};
