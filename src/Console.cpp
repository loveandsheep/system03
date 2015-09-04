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
	
	unitMesh.clear();
	loadMeshManual();
	
	unitNode.setPosition(0, -10, 0);

	unitLinkNode[0].setParent(unitNode);
	unitLinkNode[1].setParent(unitNode);
	unitLinkNode[2].setParent(unitNode);

	unitLinkNode[0].setPosition(40.0, 26.0, 0.0);
	unitLinkNode[1].setPosition(-40.0, 26.0, 0.0);
	unitLinkNode[2].setPosition(0, -44, 0.0);

	
	camera.setDistance(300);
	camera.rotateAround(-135, ofVec3f(0.0,1.0,0.0), ofVec3f(0.0, 0.0, 0.0));
	camera.lookAt(ofVec3f(0, 0, 0));
	camera.disableMouseInput();
	
	themeColor.setHsb(0.45, 1.0, 1.0);
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
//	glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA,GL_ONE);
	
	ofClear(0, 0, 0, 255);
	
	ofSetColor(30);
	for (int i = 0;i <= 800;i+=4)
	{
//		ofLine(0, i, 480, i);
	}
	
	
	ofSetColor(255);
	
	/* Unit drawing */
	drawPatternUnit();
	drawUnit();
	drawAnglePattern();
	drawMotorGraph();

	/*
	ofSetColor(255);
	string info = "Sys03:Console\n";
	info += "fps - " + ofToString(ofGetFrameRate()) + "\n";
	info += "laserState - " + string(sysPtr->laserState ? "1\n" : "0\n");
	info += "patternID - " + ofToString(pointPtr->pattern_id) + "\n";
	info += "patternIndex - " + ofToString(pointPtr->posIndex) + "\n";
	info += "tipHeading - " + ofToString(sysPtr->eyes.arm[0].tipNode()->getHeading()) + "\n";
	ofDrawBitmapString(info, 15, 280);
	*/
	
	buffer.end();
	
	ofSetColor(255);
}

void Console::drawPatternUnit()
{
	vector<ofFloatColor> colors;
	vector<ofVec2f> vertices;
	gridPattern* currentPt = &pointPtr->patterns[pointPtr->pattern_id];
	for (int i = 0;i < currentPt->pos.size();i++)
	{
		colors.push_back(currentPt->pen[i] ? ofFloatColor(1.0,1.0,1.0,1.0) : ofFloatColor(0.0,0.0,0.0,1.0));
		colors.push_back(currentPt->pen[i] ? ofFloatColor(1.0,1.0,1.0,1.0) : ofFloatColor(0.0,0.0,0.0,1.0));
		vertices.push_back(currentPt->pos[i]);
		vertices.push_back(currentPt->pos[(i+1) % currentPt->pos.size()]);
	}
	
	float sc = 50.0;
	
	ofPushMatrix();
	ofTranslate(366, 700);
	ofTranslate(currentTarg_smooth * sc);
	float ll = 1500.0;
	
	ofSetColor(themeColor, 128);
	ofLine(-ll, 0, ll, 0);
	ofLine(0, -ll, 0, ll);
	
	ofTranslate(10, 0);
	drawCode(currentTarg_smooth.x * pointPtr->Gridscale * 32.1324);
	ofTranslate(0, 5);
	drawCode(currentTarg_smooth.y * pointPtr->Gridscale * 32.1324);
	ofPopMatrix();
	
	ofPushMatrix();
	{
		ofSetColor(255);
		ofTranslate(366, 700);
		
		glScalef(sc, sc, sc);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);
		glColorPointer(4, GL_FLOAT, 0, &colors[0]);
		glDrawArrays(GL_LINE_LOOP, 0, vertices.size());
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		
		currentTarg_smooth += (pointPtr->target / pointPtr->Gridscale - currentTarg_smooth) / 2.0;
	}
	ofPopMatrix();
}

void Console::drawMotorGraph()
{
	for (int i = 0;i < 3;i++)
	{
		motor_smooth[i] += ((sysPtr->motor_pos[i] - 12800) / 15.0 - motor_smooth[i]) / 5.0;
		
		ofPushMatrix();
		ofTranslate(80, 80 + i * 70);
		drawMotorAngle(motor_smooth[i] + 90);
		
		/* Grid line */
		static vector<ofVec2f> grids;
		static bool gb = false;
		if (!gb)
		{
			gb = true;
			for (int j = -200;j < 500;j+=10)
			{
				grids.push_back(ofVec2f(j, -2));
				grids.push_back(ofVec2f(j,  2));
			}
		}
		
		ofSetColor(100);
		ofLine(-200, 0, 500, 0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, &grids[0]);
		glDrawArrays(GL_LINES, 0, grids.size());
		glDisableClientState(GL_VERTEX_ARRAY);
		
		for (int j = -200;j < 500;j+=10)
			ofLine(j, -2, j, 2);
		
		/* Graph */
		ofSetColor(255);
		vector<ofVec2f> logline;
		for (int j = 0;j < motorlog[i].size();j++)
		{
			logline.push_back(ofVec2f(j * 3 + 25, 0));
			logline.push_back(ofVec2f(j * 3 + 25, motorlog[i][j]));
		}
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, &logline[0]);
		glDrawArrays(GL_LINES, 0, logline.size());
		glDisableClientState(GL_VERTEX_ARRAY);
		
		/* Codes */
		ofPushMatrix();
		{
			ofTranslate(-65, -3);
			drawCode(motor_smooth[i]);
		}
		ofPopMatrix();
		
		ofPopMatrix();
		
		motorlog[i].push_front(sin(ofDegToRad(motor_smooth[i])) * 25);
		while (motorlog[i].size() > 150) {
			motorlog[i].pop_back();
		}
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
			ofSetColor(0);
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
		
		ofLine(0, 10 * (i == 2 ? -1.0 : 1.0), 60, 80 * (i == 2 ? -1.0 : 1.0));
		
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
	
	ofVec2f verts[64];
	ofFloatColor colors[64];
	
	for (int i = 0;i < sizeof(v) * 8;i++)
	{
		if ((c[i/8] >> (i % 8)) & 0x01)
		{
			colors[i*2  ].set(0.0,0.0,0.0,1.0);
			colors[i*2+1].set(0.0,0.0,0.0,1.0);
		}
		else
		{
			colors[i*2  ].set(1.0,1.0,1.0,1.0);
			colors[i*2+1].set(1.0,1.0,1.0,1.0);
		}
		verts[i*2].set(i, 0);
		verts[i*2+1].set(i, 5);
	}
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, verts);
	glColorPointer(4, GL_FLOAT, 0, colors);
	glDrawArrays(GL_LINES, 0, 64);
	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
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
