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
	addScene<geom_triangle>();
	addScene<geom_rectangle>();
	addScene<geom_hexagon>();
	
	for (int i = 0;i < scenes.size();i++){
		scenes[i]->setupBasis();
	}
	
	setScene(0);
}

void geomManager::update()
{
	ofPtr<baseGeometry> current = scenes[curScnIdx];

	current->updateBasis();
	if (current->trail_pos == 1.0f)
	{
		setScene(ofRandom(100));
		scenes[curScnIdx]->trail_pos = 0.0;
	}
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

