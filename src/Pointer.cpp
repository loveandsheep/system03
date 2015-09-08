//
//  Pointer.cpp
//  system03
//
//  Created by Ovis aries on 2015/08/28.
//
//

#include "Pointer.h"

void Pointer::init()
{
	Gridscale = 35.0;
	target.set(ofRandomf() * Gridscale,
			   ofRandomf() * Gridscale);

	genMotorPattern(true);
	
	pattern_id = int(ofRandom(100)) % patterns.size();
	posIndex = 0;
	loopCounter = 0;
	
	interval_point =10;
	interval_pattern = interval_point;
	interval_long = 500;
	
	phase = PHASE_POINTING;
	phaseCount = 0;
}

void Pointer::update()
{
	if (phase == PHASE_POINTING)
	{
		target = patterns[pattern_id]->pos[posIndex] * Gridscale;
		phaseCount++;
		if (phaseCount >= interval_point)
		{
			goNextPoint();
			phaseCount = 0;
		}
		if (posIndex >= patterns[pattern_id]->pos.size())
		{
			laserState = false;
			phase = PHASE_IDLE;
			phaseCount = 0;
		}
	}
	if (phase == PHASE_IDLE)
	{
//		target.set(0, 0);
		
		phaseCount++;
		if (phaseCount >= interval_pattern)
		{
			phase = PHASE_POINTING;
			phaseCount = 0;
			goNextPattern();
		}

	}
}

void Pointer::view()
{
	
}

bool Pointer::getCurrentLaser()
{
	return laserState;
}

void Pointer::goNextPoint()
{
	laserState = patterns[pattern_id]->pen[posIndex];
	posIndex++;
}

void Pointer::goNextPattern(int manual)
{
	loopCounter++;
	posIndex = 0;
	
	initPatterns();
	pattern_id = int(ofRandom(100)) % patterns.size();
	posIndex = 0;
	
	interval_pattern = interval_point;
	
	if (loopCounter > 20)
	{
		loopCounter = 0;
		interval_pattern = interval_long;
	}
}

void Pointer::genMotorPattern(bool randomize)
{
	beginPattern();
	
	for (int i = 0;i < 3;i++)
	{
		float deg = randomize ? ofRandomf() * 6 : (sysPtr->motor_pos[i] - 12800) * 6;
		addVertex(sin(deg), cos(deg), true);
	}
	
	float deg = randomize ? ofRandomf() * 6 : (sysPtr->motor_pos[0] - 12800) * 6;
	addVertex(sin(deg), cos(deg), false);

	endPattern();
}

void Pointer::initPatterns()
{
	patterns.clear();

	genMotorPattern();
	return;
	
	bool en_CircleRandom	= true;
	bool en_TriangleRot		= true;
	bool en_LineRot			= true;
	bool en_circleTriangle	= false;
	bool en_grid			= false;
	bool en_grid_45			= true;

	
	if (en_grid_45)
	{
		beginPattern();
		for (int i = 0;i < 20;i++)
		{
			if (ofRandomuf() < 0.5)
			{
				ofVec2f ax = ofVec2f(ofRandomf(), -1.0);
				addVertex(ax.x, ax.y, true);
				addVertex(ax.y, ax.x, false);
			}else{
				ofVec2f ax = ofVec2f(1.0, ofRandomf());
				addVertex(ax.x, ax.y, true);
				addVertex(ax.y, ax.x, false);
			}
		}
		endPattern();
	}
	
	//grid
	if (en_grid)
	{
		beginPattern();
		for (int i = 0;i < 20;i++)
		{
			if (ofRandomuf() < 0.5)
			{
				float x = ofRandomf();
				addVertex(x, -1.0, true);
				addVertex(x,  1.0, false);
			}else{
				float y = ofRandomf();
				addVertex(-1.0, y, true);
				addVertex( 1.0, y, false);
			}
		}
		endPattern();
	}
	
	//circleTriangle
	if (en_circleTriangle)
	{
		beginPattern();
		for (int i = 0;i < 10;i++)
		{
			float deg = ofRandom(-PI * 2);
			addVertex(-1.0, 0.0, true);
			addVertex( 1.0, 0.0, true);
			addVertex(cos(deg), sin(deg), true);
			addVertex(-1.0, 0.0, true);
		}
		endPattern();
	}
	
	//Circle
	if (en_CircleRandom){
		beginPattern();
		float seed = ofRandomf();
		for (int i = 0;i <= 100;i++)
		{
			float deg = powf(2.0, ofNoise(i * 2.0 * PI + seed * 3941.341)) * 10.0;
			addVertex(cos(deg),
					  sin(deg), true);
		}
		endPattern();
	}
	
	//TriangleRot
	if (en_TriangleRot){
		beginPattern();
		float deg[3], rad[3];
		for (int i = 0;i < 3;i++)
		{
			deg[i] = ofRandomf() + i * 2;
			rad[i] = ofRandom(0.5,1.0);
		}
		for (int i = 0;i < 15;i++)
		{
			for (int j = 0;j < 3;j++)
			{
				addVertex(cos(deg[j]) * rad[j], sin(deg[j]) * rad[j], true);
			}
			addVertex(cos(deg[0]) * rad[0], sin(deg[0]) * rad[0], false);
			for (int j = 0;j < 3;j++) deg[j] += 0.05 * (i + 1);
		}
		endPattern();
	}
	
	//LineRot
	if (en_LineRot){
		beginPattern();
		float deg[3], rad[3];
		for (int i = 0;i < 2;i++)
		{
			deg[i] = ofRandomf() + i * 2;
			rad[i] = ofRandom(0.5,1.0);
		}
		for (int i = 0;i < 30;i++)
		{
			addVertex(cos(deg[0]) * rad[0], sin(deg[0]) * rad[0], true);
			addVertex(cos(deg[1]) * rad[1], sin(deg[1]) * rad[1], false);
			for (int j = 0;j < 2;j++) deg[j] += 0.1 + (i * 0.01);
		}
		endPattern();
	}
	
}

void Pointer::beginPattern()
{
	tmpPattern.pen.clear();
	tmpPattern.pos.clear();
}

void Pointer::addVertex(float x, float y, bool pen)
{
	tmpPattern.pen.push_back(bool(pen));
	tmpPattern.pos.push_back(ofVec2f(x, y));
}

void Pointer::endPattern()
{
	ofPtr<gridPattern> gp = ofPtr<gridPattern>(new gridPattern(tmpPattern));
	patterns.push_back(gp);
}