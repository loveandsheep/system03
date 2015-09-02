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
	buffer.begin();
	ofClear(0, 0, 0, 255);
	
	ofDrawBitmapString(ofToString(sysPtr->motor_pos[0]), 30,30);
	ofSetColor(255, 0, 0);
	ofNoFill();
	ofRect(1, 1, 599, 799);
	ofFill();
	
	for (int i = 0;i < 600;i+=10)
	{
		ofSetColor(255, 0, 0);
		if (i % 100 == 0) ofSetColor(255, 255, 0);
		ofLine(i, 0, i, 50);
	}
	for (int j = 0;j < 800;j+=10)
	{
		ofSetColor(255, 0, 0);
		if (j % 100 == 0) ofSetColor(255, 255, 0);
		ofLine(0, j, 50, j);
	}
	
	buffer.end();
	
	ofSetColor(255);
}