//
//  Console.cpp
//  system03
//
//  Created by Ovis aries on 2015/08/31.
//
//

#include "Console.h"

void Console::init()
{
	buffer.allocate(480, 800);
	
	ofxObjLoader::load("unit.obj", unitMesh);
	unitNode.setPosition(0, 0, 23);

	unitLinkNode[0].setParent(unitNode);
	unitLinkNode[1].setParent(unitNode);
	unitLinkNode[2].setParent(unitNode);

	unitLinkNode[0].setPosition(40.0, 26.0, 0.0);
	unitLinkNode[1].setPosition(-40.0, 26.0, 0.0);
	unitLinkNode[2].setPosition(0, -44, 0.0);

	
	camera.setDistance(300);
	camera.rotateAround(-90, ofVec3f(0.0,1.0,0.0), ofVec3f(0.0, 0.0, 0.0));
	camera.lookAt(ofVec3f(0, 0, 0));
	camera.disableMouseInput();
	
}

void Console::update()
{
	
}

void Console::view()
{

	/*====== Viewing Datas ========*/

	//モーター位置
	sysPtr->motor_pos[0] - 12800;
	sysPtr->motor_pos[1] - 12800;
	sysPtr->motor_pos[2] - 12800;
	
	pointPtr->target;//ポイント座標
	pointPtr->patterns;//パターン形状
	sysPtr->laserState;//レーザー状態
	sysPtr->eyes.arm[0].rootPan;//ルート角度 = モーター位置
	sysPtr->eyes.arm[0].tipNode()->getHeading();//先端角度
	sysPtr->eyes.eye.center;//ユニットノード情報
	/*====== Viewing Datas ========*/
	
	buffer.begin();
	glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA,GL_ONE);
	
	ofClear(0, 0, 0, 255);
	
	
	ofSetColor(255);
	
	ofNoFill();
//	ofRect(1, 1,478,798);
	ofFill();
	
	/* Unit drawing */
	cout << ofGetMouseX() << "," << ofGetMouseY() << endl;
	drawUnit();
	drawAnglePattern();
	
	drawMotorGraph();
	
	buffer.end();
	
	ofSetColor(255);
}

void Console::drawMotorGraph()
{
	for (int i = 0;i < 3;i++)
	{
		motor_smooth[i] += ((sysPtr->motor_pos[i] - 12800) / 20.0 - motor_smooth[i]) / 5.0;
		
		ofPushMatrix();
		ofTranslate(80, 80 + i * 70);
		drawMotorAngle(motor_smooth[i] + 90);
		
		ofSetColor(100);
		ofLine(-200, 0, 500, 0);
		
		for (int j = -200;j < 500;j+=10)
			ofLine(j, -2, j, 2);
		
		ofPushMatrix();
		ofTranslate(-65, -3);
		drawCode(motor_smooth[i]);
		ofPopMatrix();
		
		ofPopMatrix();
	}
}

void Console::drawUnit()
{
	ofPushMatrix();
	{
		camera.begin();
		const float size = 20.0;
		ofQuaternion qq;
		qq.slerp(0.25,
				 unitNode.getGlobalOrientation(),
				 sysPtr->eyes.eye.center.getGlobalOrientation());
		unitNode.setGlobalOrientation(qq);
		
		glScalef(-1.0, 1.0, 1.0);
		
		ofPushMatrix();
		{
			ofMultMatrix(unitNode.getGlobalTransformMatrix());

			glScalef(size, size, size);
			ofEnableDepthTest();
			ofSetColor(255);
			glLineWidth(2.0);
			unitMesh.drawWireframe();
			glLineWidth(1.0);
			ofSetColor(0,175);
			unitMesh.drawFaces();
			ofDisableDepthTest();
		}
		ofPopMatrix();
		
		ofSetColor(255);
		//		ofDrawBox(unitLinkNode[0].getGlobalPosition()/20.0, 0.2);
		//		ofDrawBox(unitLinkNode[1].getGlobalPosition()/20.0, 0.2);
		//		ofDrawBox(unitLinkNode[2].getGlobalPosition()/20.0, 0.2);
		
		camera.end();
	}
	ofPopMatrix();
}

void Console::drawAnglePattern()
{
	ofVec3f link[3];
	for (int i = 0;i < 3;i++)
	{
		link[i] = camera.worldToScreen(unitLinkNode[i].getGlobalPosition() * ofVec3f(-1.0,1.0,1.0));
		
		ofVec2f pt = link[i];
		
		ofPushMatrix();
		ofTranslate(pt);
		if (i == 0) ofTranslate(0, 20);
		ofTranslate(-60, -80 * (i == 2 ? -1.0 : 1.0));
		
		ofLine(0, 0, 60, 80 * (i == 2 ? -1.0 : 1.0));
		
		for (int j = 0;j < 3;j++)
		{
			drawCode(camera.worldToScreen(unitLinkNode[i].getGlobalPosition() * ofVec3f(-1.0,1.0,1.0))[j]);
			ofTranslate(32, 0);
		}
		ofPopMatrix();
		
	}
}

void Console::drawCode(float v)
{
	unsigned char c[sizeof(v)];
	memcpy(c, &v, sizeof(v));
	
	for (int i = 0;i < sizeof(v) * 8;i++)
	{
		ofSetColor(255);
		if ((c[i/8] >> (i % 8)) & 0x01) ofSetColor(0, 0, 0);
		ofLine(i, 0, i, 5);
	}
}

void Console::drawMotorAngle(float angle)
{
	float radius = 25.0;
	
	vector<ofVec3f> memori;
	for (int i = 0;i <= 360;i+=10)
	{
		float bigMem = i % 90 == 0 ? 0.9 : 1.0;
		memori.push_back(ofVec3f(cos(ofDegToRad(i)) * radius,
								 sin(ofDegToRad(i)) * radius));
		memori.push_back(ofVec3f(cos(ofDegToRad(i)) * radius * 0.9 * bigMem,
								 sin(ofDegToRad(i)) * radius * 0.9 * bigMem));
	}
	
	ofSetColor(255);
	ofPushMatrix();
	ofRotateZ(angle);
	glLineWidth(1.0);
	
	glLineWidth(2.0);
//	ofLine(-radius/4, 0, radius/4, 0);
	ofLine(0, -radius, 0, 0);
	glLineWidth(1.0);
	
	ofSetColor(255);

	glLineWidth(1.0);
	ofPopMatrix();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &memori[0]);
	glDrawArrays(GL_LINES, 0, memori.size());
	glDisableClientState(GL_VERTEX_ARRAY);

}