#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	camera.setDistance(300);
	
	sys03.init();
	receiver.setup(54503);

	manual = true;
	
	geometries.setup();
	
	targetPoint.set(0, 0, 0);
	
#ifndef TARGET_OSX
	pinMode(LASER_PIN, OUTPUT);
	digitalWrite(LASER_PIN, 1);
#endif

}

//--------------------------------------------------------------
void ofApp::update(){
	
	
	oscManage();

	if (!manual)
	{
		/*描画シーン*/
		geometries.update();
#ifndef TARGET_OSX
		digitalWrite(LASER_PIN,
					 geometries.getCurrentScene()->targLaser);
#endif
	}
	
	if (targetPoint != previousPoint)
	{
		sys03.motor.enableAllMotor();
		sys03.update(targetPoint);		
	}
	previousPoint = targetPoint;
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(20);
	if (geometries.getCurrentScene()->targLaser) ofBackground(0, 0, 50);
	
	camera.begin();
	geometries.getCurrentScene()->drawPath();
	
	sys03.view();
	camera.end();
	
}

void ofApp::exit(){
	sys03.sendDefaultPos();
	sys03.motor.sendSignal(RPI_L6470_SIG_STOP_HARD, 0);

#ifndef TARGET_OSX
	digitalWrite(LASER_PIN, 0);
#endif
}

void ofApp::oscManage()
{
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
		
		if (m.getAddress() == "/system03/stop")
			sys03.motor.sendSignal(RPI_L6470_SIG_STOP_HARD, 0);
		
		if (m.getAddress() == "/system03/signal")
			sys03.motor.sendSignal((unsigned char)(m.getArgAsInt32(0)),
								   m.getArgAsInt32(1));
	}
}