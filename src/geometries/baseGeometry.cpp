//
//  baseGeometry.cpp
//  system03
//
//  Created by Ovis aries on 2015/07/21.
//
//

#include "baseGeometry.h"

void baseGeometry::setupBasis()
{
	targPos.set(0,0,0);
	
	trail_speed = 0.003;
	trail_pos = 0.0;
	
	setup();
	
}

void baseGeometry::updateBasis()
{
	update();
}

void baseGeometry::update()
{
	trail_pos += trail_speed;
	trail_pos = MIN(1.0,trail_pos);
	targPos = getInterpolated(trail_pos);
	targLaser = color[getInterpolateIndex(trail_pos)].r > 0.5;
}

void baseGeometry::addPath(ofVec3f p, bool laser)
{
	if (path.size() > 0)
	{
		path.push_back(ofVec3f(path.back()));
		color.push_back(ofFloatColor(laser ? 1.0 : 0.0));
	}
	
	path.push_back(ofVec3f(p));
	color.push_back(ofFloatColor(laser ? 1.0 : 0.0));

	refleshLength();
}

void baseGeometry::refleshLength()
{
	lengths.clear();
	length_total = 0.0;
	
	for (int i = 0;i < path.size() - 1;i++)
	{
		lengths.push_back(path[i].distance(path[i+1]));
		length_total += lengths.back();
	}
}

ofVec3f baseGeometry::getInterpolated(float pct)
{
	pct = ofClamp(pct, 0.001, 0.999);
	
	float targL = length_total * pct;
	int tIdx = 0;
	
	while (targL > lengths[tIdx]) {
		targL -= lengths[tIdx];
		tIdx++;
	}
	
	float intpL = targL / lengths[tIdx];

	return path[tIdx].interpolated(path[tIdx + 1], intpL);
}

int baseGeometry::getInterpolateIndex(float pct)
{
	pct = ofClamp(pct, 0.001, 0.999);
	
	float targL = length_total * pct;
	int tIdx = 0;
	
	while (targL > lengths[tIdx]) {
		targL -= lengths[tIdx];
		tIdx++;
	}
	
	return tIdx;
}

void baseGeometry::drawPath()
{
	ofPushMatrix();
	ofRotateZ(180);
	ofRotateY(-135);
	ofTranslate(-200, -200, 200);
	ofRotateY(-45);
	
	ofDrawBox(targPos, 30);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, &path[0]);
	glColorPointer(4, GL_FLOAT, 0, &color[0]);

	glDrawArrays(GL_LINE_STRIP, 0, path.size());
	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	ofPopMatrix();
}