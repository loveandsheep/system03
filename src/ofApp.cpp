#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetFrameRate(30);
	
	camera.setDistance(300);
	receiver.setup(54503);
	targetPoint.set(0, 0, 0);
	
	sys03.init();
	sys03.setLaser(true);

	pointer.sysPtr = &sys03;
	pointer.init();
	
	manual = false;
	
	console.pointPtr = &pointer;
	console.sysPtr = &sys03;
	console.init();

}

//--------------------------------------------------------------
void ofApp::update(){
	
	ofHideCursor();
	
	oscManage();
	pointer.update();
	console.update();
	
	if (!manual)
	{
		/*描画シーン*/
		targetPoint = pointer.target;
		sys03.setLaser(pointer.getCurrentLaser());
	}

	/*ポイントの更新*/
	sys03.update();
	
	if (targetPoint != previousPoint)
	{
		sys03.motor.enableAllMotor();
		sys03.updateTarg(targetPoint);
	}
	
	previousPoint = targetPoint;
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(0);
	console.view();
	
	camera.begin();
	{
//		sys03.view();
	}
	camera.end();

#ifdef TARGET_OSX
	console.buffer.draw(0, 0);
#else
	ofPushMatrix();
	ofTranslate(0, ofGetHeight());
	ofRotateZ(-90);
	ofTranslate(0, 0);
	console.buffer.draw(ofGetHeight() - 480, 0);
	ofPopMatrix();
#endif
	
}

void ofApp::exit()
{
	sys03.motor.sendSignal(RPI_L6470_SIG_STOP_HARD, 0);
	sleep(1);
	sys03.sendDefaultPos();
	sys03.setLaser(false);
#ifndef TARGET_OSX
	digitalWrite(LIGHT_PIN, false);
#endif
}

void ofApp::oscManage()
{
	while (receiver.hasWaitingMessages())
	{
		ofxOscMessage m;
		receiver.getNextMessage(&m);
		
		if (m.getAddress() == "/system03/gpio")
			sys03.setLaser(m.getArgAsInt32(0));
		
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
		
		if (m.getAddress() == "/system03/interval/point")
			pointer.interval_point = m.getArgAsInt32(0);
		
		if (m.getAddress() == "/system03/interval/pattern")
			pointer.interval_pattern = m.getArgAsInt32(0);
		

	}
}