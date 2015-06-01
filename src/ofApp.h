#pragma once

#include "ofMain.h"
#include "fontPointer.h"
#include "system03.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	fontPointer fontPt;
	system03 sys03;
};
