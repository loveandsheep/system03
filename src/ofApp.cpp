#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	camera.setDistance(300);
	receiver.setup(54503);
	targetPoint.set(0, 0, 0);
	pointer.init();
	
	sys03.init();
	sys03.setLaser(true);
	
	manual = false;
	
	console.pointPtr = &pointer;
	console.sysPtr = &sys03;
	console.init();

}

//--------------------------------------------------------------
void ofApp::update(){
	
	
	oscManage();
	pointer.update();
	console.update();
	
	if (!manual)
	{
		/*描画シーン*/
		targetPoint = pointer.target;
//		sys03.setLaser()
		
	}

	/*ポイントの更新*/
	//TODO: 更新間隔を誰に握らせるか
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
	console.view();
	
	camera.begin();
	{
		sys03.view();
	}
	camera.end();
	
	console.buffer.draw(0, 0);
}

void ofApp::exit()
{
	sys03.motor.sendSignal(RPI_L6470_SIG_STOP_HARD, 0);
	sleep(1);
	sys03.sendDefaultPos();
	sys03.setLaser(false);
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
	}
}