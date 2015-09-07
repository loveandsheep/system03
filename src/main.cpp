#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	
#ifdef TARGET_OSX
	ofSetupOpenGL(480,800,OF_WINDOW);			// <-------- setup the GL context
#else
	ofSetupOpenGL(1024,1024,OF_WINDOW);			// <-------- setup the GL context
#endif
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
