#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	fontPt.setup("font/Curveless.ttf", 0.5, "test");
	
	
}

//--------------------------------------------------------------
void ofApp::update(){
	
	fontPt.update();

}

//--------------------------------------------------------------
void ofApp::draw(){

	fontPt.drawDebug();
	
}