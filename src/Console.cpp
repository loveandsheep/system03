//
//  Console.cpp
//  system03
//
//  Created by Ovis aries on 2015/08/31.
//
//

#include "Console.h"

void Console::init()
{
	buffer.allocate(600, 800);
}

void Console::update()
{
	
}

void Console::view()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	buffer.begin();
	ofClear(0, 0, 0, 255);
	
	ofDrawBitmapString(ofToString(sysPtr->motor_pos[0]), 30,30);
	ofSetColor(255, 0, 0);
	ofNoFill();
	ofRect(1, 1, 599, 799);
	ofFill();
	
	buffer.end();
	glPopAttrib();
}