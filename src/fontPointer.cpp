//
//  fontDrawer.cpp
//  system03
//
//  Created by Ovis aries on 2015/06/01.
//
//

#include "fontPointer.h"

void fontPointer::setup(string path, float _scale, string viewStr)
{

	font.loadFont(path, 72);
	scale = _scale;
	
	setSentence(viewStr);
	
}

void fontPointer::update()
{
	
	if (outlines.size() > 0 && ofGetFrameNum() % 3 == 0){
		pathCount++;
		if (outlines[outlineCount].getVertices().size() <= pathCount)
		{
			outlineCount++;
			pathCount = 0;
		}
		if (outlines.size() <= outlineCount) outlineCount = 0;
	}
	
}

void fontPointer::drawDebug()
{
	font.drawString(currentSentence, 0, 0);
}

ofVec3f fontPointer::getPoint()
{
	return scale * (ofVec3f(outlines[outlineCount].getVertices()[pathCount]) - offset);
}

void fontPointer::setSentence(string viewStr)
{

	sentence = font.getStringAsPoints(viewStr);
	outlines.clear();
	for (int i = 0;i < sentence.size();i++)
	{
		for (int j = 0;j < sentence[i].getOutline().size();j++)
		{
			outlines.push_back(sentence[i].getOutline()[j]);
			outlines.back().addVertex(outlines.back().getVertices()[0]);
		}
	}
	
	scale = 1.0;
	ofRectangle r = font.getStringBoundingBox(viewStr, 0, 0);
	offset.set(r.width / 2.0, -r.height / 2.0);
	
	outlineCount = 0;
	pathCount = 0;
	currentSentence = viewStr;
	
}