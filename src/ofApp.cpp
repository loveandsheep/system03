#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

//	fontPt.setup("font/Curveless.ttf", 0.5, "test");
//	camera.setDistance(300);
	
//	ofxRPiGPIO::setup();
//#ifdef USE_GPIO
//	ofxRPiGPIO::setPinMode(LASER_PIN, GPIO_OUTPUT);
//#endif

//	sys03.init();
	testMotor.setup(true, 1);
//	testMotor.sendSignal(RPI_L6470_SIG_VOLT_HOLD, 255);
//	testMotor.sendSignal(RPI_L6470_SIG_VOLT_ACC, 255);
//	testMotor.sendSignal(RPI_L6470_SIG_ABSPOS, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
//	fontPt.update();
	if (ofGetFrameNum() % 15 == 0){
//		testMotor.enableAllMotor();
		cout << "Send" << endl;
		testMotor.sendSpi('a');
//		testMotor.sendSignal(RPI_L6470_SIG_GOTO, ofRandom(200));
	}
//	sys03.update(fontPt.getPoint());
//	if (ofGetFrameNum() % 60 == 0) {
//		sys03.motor->setStepperAll(true);
//		sys03.motor->go_to(ofRandom(300));
//		sys03.motor->setStepperAll(false);
//	}
//	if (ofGetFrameNum() % 60 == 0) ofxRPiGPIO::setPinValue(LASER_PIN, true);
//	if (ofGetFrameNum() % 60 == 30) ofxRPiGPIO::setPinValue(LASER_PIN, false);
//	if (ofGetFrameNum() % 60 == 0) printf("Timer cout \n");
}

//--------------------------------------------------------------
void ofApp::draw(){

//	ofBackground(20);
	
//	camera.begin();
//	fontPt.drawDebug();
//	sys03.view();
//	camera.end();
	
	
	
}
