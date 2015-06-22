#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

//	fontPt.setup("font/Curveless.ttf", 0.5, "test");
//	camera.setDistance(300);
//	
//	ofxRPiGPIO::setup();
//#ifdef USE_GPIO
//	ofxRPiGPIO::setPinMode(LASER_PIN, GPIO_OUTPUT);
//#endif
//
//	sys03.init();
	spi.init();
}

//--------------------------------------------------------------
void ofApp::update(){
	spi.send1(128);
//	fontPt.update();
//	sys03.update(fontPt.getPoint());
//	if (ofGetFrameNum() % 60 == 0) ofxRPiGPIO::setPinValue(LASER_PIN, true);
//	if (ofGetFrameNum() % 60 == 30) ofxRPiGPIO::setPinValue(LASER_PIN, false);
//	if (ofGetFrameNum() % 60 == 0) printf("Timer cout \n");
}

//--------------------------------------------------------------
void ofApp::draw(){

//	ofBackground(20);
//	
//	camera.begin();
//	fontPt.drawDebug();
//	sys03.view();
//	camera.end();
	
	
	
}
