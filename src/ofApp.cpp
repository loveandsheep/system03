#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	fontPt.setup("font/Curveless.ttf", 0.5, "test");
	sys03.init();
	camera.setDistance(300);
	
	gpio.setup();
	gpio.setPinMode(4, GPIO_OUTPUT);
}

//--------------------------------------------------------------
void ofApp::update(){
	
	fontPt.update();
	sys03.update(fontPt.getPoint());
	printf("hello world");
	if (ofGetFrameNum() % 60 == 0) gpio.setPinValue(2, true);
	if (ofGetFrameNum() % 60 == 30) gpio.setPinValue(2, false);
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(20);
	
	camera.begin();
	fontPt.drawDebug();
	sys03.view();
	camera.end();
	
	
	
}