#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	fontPt.setup("font/Curveless.ttf", 0.5, "test");
	sys03.init();
	camera.setDistance(300);
	
	gpio.setup();
	gpio.setPinMode(2, GPIO_OUTPUT);
}

//--------------------------------------------------------------
void ofApp::update(){
	
	fontPt.update();
	sys03.update(fontPt.getPoint());
	
	if (ofGetFrameNum() % 60 == 0) gpio.setPinValue(2, 1);
	if (ofGetFrameNum() % 60 == 30) gpio.setPinValue(2, 0);
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(20);
	
	camera.begin();
	fontPt.drawDebug();
	sys03.view();
	camera.end();
	
	
	
}