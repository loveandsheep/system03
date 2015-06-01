#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	fontPt.setup("font/Curveless.ttf", 0.5, "test");
	sys03.init();
	camera.setDistance(300);
	
}

//--------------------------------------------------------------
void ofApp::update(){
	
	fontPt.update();
	sys03.update(fontPt.getPoint());
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(20);
	
	camera.begin();
	fontPt.drawDebug();
	sys03.view();
	camera.end();
	
}