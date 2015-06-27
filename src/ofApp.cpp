#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	fontPt.setup("font/Curveless.ttf", 0.5, "test");
	camera.setDistance(300);
	
	sys03.init();

}

//--------------------------------------------------------------
void ofApp::update(){
	fontPt.update();


	if (ofGetFrameNum() % 60 == 0){
		sys03.motor.enableAllMotor();
		vector<int> mot;
		mot.push_back(ofGetFrameNum() % 3 == 0 ? ofRandom(200 * 128) : 0);
		mot.push_back(ofGetFrameNum() % 3 == 1 ? ofRandom(200 * 128) : 0);
		mot.push_back(ofGetFrameNum() % 3 == 2 ? ofRandom(200 * 128) : 0);
		sys03.motor.setGo_toMult(mot);
	}

//		testMotor.enableAllMotor();
//		testMotor.sendSpi('a');
//		unsigned char t[] = {'a', 'b', 'v'};
//		testMotor.spi.sendN(t, 3);

//	}
	sys03.update(fontPt.getPoint());
	if (ofGetFrameNum() % 60 == 0) {
//		sys03.motor->setStepperAll(true);
//		sys03.motor->go_to(ofRandom(300));
//		sys03.motor->setStepperAll(false);
	}
//	if (ofGetFrameNum() % 60 == 0) ofxRPiGPIO::setPinValue(LASER_PIN, true);
//	if (ofGetFrameNum() % 60 == 30) ofxRPiGPIO::setPinValue(LASER_PIN, false);
//	if (ofGetFrameNum() % 60 == 0) printf("Timer cout \n");
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(20);
	
	camera.begin();
	fontPt.drawDebug();
	sys03.view();
	camera.end();

	
}
