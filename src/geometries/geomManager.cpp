//
//  geomManager.cpp
//  system03
//
//  Created by Ovis aries on 2015/07/21.
//
//

#include "geomManager.h"

void geomManager::setup()
{
	
	ofPtr<baseGeometry> scn = ofPtr<baseGeometry>(new baseGeometry);
	scenes.push_back(scn);
	
	for (auto it : scenes) it->setupBasis();
	
	setScene(0);
}

void geomManager::update()
{
	scenes[curScnIdx]->updateBasis();
}

ofVec3f geomManager::getCurrentTargpos()
{
	return scenes[curScnIdx]->targPos;
}

bool geomManager::getCurrentLaser()
{
	return scenes[curScnIdx]->targLaser;
}

void geomManager::setScene(int num)
{
	num = num % scenes.size();
	curScnIdx = num;
}

