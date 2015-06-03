#pragma once

#include "ofMain.h"
#include "fontPointer.h"
#include "system03.h"

#include "ofxRPiGPIO.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	ofEasyCam camera;
	fontPointer fontPt;
	system03 sys03;

	ofxRPiGPIO gpio;
};
