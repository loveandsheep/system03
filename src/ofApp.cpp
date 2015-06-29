#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	fontPt.setup("font/Curveless.ttf", 0.5, "test");
	camera.setDistance(300);
	
	sys03.init();
	receiver.setup(54503);

	manual = false;
	targetPoint.set(0, 0, 0);
	
#ifndef TARGET_OSX
	pinMode(LASER_PIN, OUTPUT);
	digitalWrite(LASER_PIN, 1);
#endif
}

//--------------------------------------------------------------
void ofApp::update(){

	while (receiver.hasWaitingMessages())
	{
		ofxOscMessage m;
		receiver.getNextMessage(&m);
		
#ifndef TARGET_OSX
		if (m.getAddress() == "/system03/gpio")
			digitalWrite(LASER_PIN, m.getArgAsInt32(0));
#endif
		
		if (m.getAddress() == "/system03/default")
			sys03.goDefault = m.getArgAsInt32(0);
		
		if (m.getAddress() == "/system03/manual")
			manual = m.getArgAsInt32(0);

		if (m.getAddress() == "/system03/point")
			targetPoint.set(m.getArgAsFloat(0),
							m.getArgAsFloat(1),
							m.getArgAsFloat(2));
			
	}

	fontPt.update();
	
	if (!manual) targetPoint = fontPt.getPoint();
	sys03.update(targetPoint);
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(20);
	
	camera.begin();
//	fontPt.drawDebug();
	sys03.view();
	camera.end();

	
}

void ofApp::exit(){
	sys03.sendDefaultPos();
#ifndef TARGET_OSX
	digitalWrite(LASER_PIN, 0);
#endif
}
