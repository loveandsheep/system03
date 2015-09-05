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
	Gridscale = 40.0;
	initPatterns();
	
	pattern_id = 0;
	posIndex = 0;
	loopCounter = 0;
	
	interval_point = 60;
	interval_pattern = 120;
	phase = PHASE_POINTING;
	phaseCount = 0;
}

void Pointer::update()
{
	

	if (phase == PHASE_POINTING)
	{
		target = patterns[pattern_id].pos[posIndex] * Gridscale;
		phaseCount++;
		if (phaseCount >= interval_point)
		{
			goNextPoint();
			phaseCount = 0;
		}
		if (posIndex >= patterns[pattern_id].pos.size())
		{
			laserState = false;
			phase = PHASE_IDLE;
			phaseCount = 0;
		}
	}
	if (phase == PHASE_IDLE)
	{
		target.set(0, 0);
		
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
	laserState = patterns[pattern_id].pen[posIndex];
	posIndex++;
}

void Pointer::goNextPattern(int manual)
{
	loopCounter++;
	posIndex = 0;
	
	if (loopCounter > 3)
	{
		pattern_id = int(ofRandom(100)) % patterns.size();
		posIndex = 0;
		loopCounter = 0;
	}
}

void Pointer::initPatterns()
{
	
	//A
	gridPattern p_A;
	p_A.pen.push_back(1); p_A.pos.push_back(ofVec2f( 0,-1));
	p_A.pen.push_back(0); p_A.pos.push_back(ofVec2f(-1, 0));
	p_A.pen.push_back(1); p_A.pos.push_back(ofVec2f( 1,-1));
	p_A.pen.push_back(0); p_A.pos.push_back(ofVec2f(-1, 1));
	p_A.pen.push_back(1); p_A.pos.push_back(ofVec2f( 1, 0));
	p_A.pen.push_back(0); p_A.pos.push_back(ofVec2f( 0, 1));
	patterns.push_back(p_A);
	
	gridPattern p_B;
	p_B.pen.push_back(1); p_B.pos.push_back(ofVec2f(-1,-1));
	p_B.pen.push_back(1); p_B.pos.push_back(ofVec2f( 1,-1));
	p_B.pen.push_back(1); p_B.pos.push_back(ofVec2f( 1, 1));
	p_B.pen.push_back(1); p_B.pos.push_back(ofVec2f(-1, 1));
	patterns.push_back(p_B);
	
	gridPattern p_C;
	p_C.pen.push_back(1); p_C.pos.push_back(ofVec2f( 0,-1));
	p_C.pen.push_back(1); p_C.pos.push_back(ofVec2f(-1, 0));
	p_C.pen.push_back(1); p_C.pos.push_back(ofVec2f( 0, 0));
	p_C.pen.push_back(1); p_C.pos.push_back(ofVec2f( 0, 1));
	p_C.pen.push_back(1); p_C.pos.push_back(ofVec2f( 1, 0));
	p_C.pen.push_back(1); p_C.pos.push_back(ofVec2f( 0, 0));
	patterns.push_back(p_C);

	gridPattern p_D;
	p_D.pen.push_back(1); p_D.pos.push_back(ofVec2f(-1,-1));
	p_D.pen.push_back(0); p_D.pos.push_back(ofVec2f( 1,-1));
	p_D.pen.push_back(1); p_D.pos.push_back(ofVec2f(-1, 0));
	p_D.pen.push_back(0); p_D.pos.push_back(ofVec2f( 1, 0));
	p_D.pen.push_back(1); p_D.pos.push_back(ofVec2f(-1, 1));
	p_D.pen.push_back(0); p_D.pos.push_back(ofVec2f( 1, 1));
	patterns.push_back(p_D);
	
	gridPattern p_E;
	p_E.pen.push_back(1); p_E.pos.push_back(ofVec2f(-1,-1));
	p_E.pen.push_back(1); p_E.pos.push_back(ofVec2f(-1,-0.5));
	p_E.pen.push_back(1); p_E.pos.push_back(ofVec2f(-0.5,-0.5));
	p_E.pen.push_back(1); p_E.pos.push_back(ofVec2f(-0.5,-1));
	p_E.pen.push_back(1); p_E.pos.push_back(ofVec2f(0.5,-1));
	p_E.pen.push_back(1); p_E.pos.push_back(ofVec2f(0.5,-0.5));
	p_E.pen.push_back(1); p_E.pos.push_back(ofVec2f(0,-0.5));
	p_E.pen.push_back(1); p_E.pos.push_back(ofVec2f(0,0.5));
	p_E.pen.push_back(1); p_E.pos.push_back(ofVec2f(-1,0.5));
	p_E.pen.push_back(1); p_E.pos.push_back(ofVec2f(-1,0));
	p_E.pen.push_back(1); p_E.pos.push_back(ofVec2f(0.5,0));
	p_E.pen.push_back(1); p_E.pos.push_back(ofVec2f(0.5,0.75));
	p_E.pen.push_back(1); p_E.pos.push_back(ofVec2f(-0.5,0.75));
	p_E.pen.push_back(1); p_E.pos.push_back(ofVec2f(-0.5,1.0));
	p_E.pen.push_back(0); p_E.pos.push_back(ofVec2f(1,1));
	patterns.push_back(p_E);
	
	gridPattern p_F;
	p_F.pen.push_back(1); p_F.pos.push_back(ofVec2f(-1, 0));
	p_F.pen.push_back(1); p_F.pos.push_back(ofVec2f( 0, 0));
	p_F.pen.push_back(1); p_F.pos.push_back(ofVec2f( 1, 0));
	p_F.pen.push_back(1); p_F.pos.push_back(ofVec2f( 1, 1));
	p_F.pen.push_back(1); p_F.pos.push_back(ofVec2f( 0, 1));
	p_F.pen.push_back(1); p_F.pos.push_back(ofVec2f( 0, 0));
	p_F.pen.push_back(1); p_F.pos.push_back(ofVec2f( 0,-1));
	p_F.pen.push_back(1); p_F.pos.push_back(ofVec2f(-1,-1));
	patterns.push_back(p_F);
	
	gridPattern p_G;
	p_G.pen.push_back(1); p_G.pos.push_back(ofVec2f(-1,-1));
	p_G.pen.push_back(1); p_G.pos.push_back(ofVec2f( 1,-1));
	p_G.pen.push_back(1); p_G.pos.push_back(ofVec2f(-1, 0));
	p_G.pen.push_back(1); p_G.pos.push_back(ofVec2f( 1, 0));
	p_G.pen.push_back(1); p_G.pos.push_back(ofVec2f(-1, 1));
	p_G.pen.push_back(0); p_G.pos.push_back(ofVec2f( 1, 1));
	patterns.push_back(p_G);

	gridPattern p_H;
	p_H.pen.push_back(1); p_H.pos.push_back(ofVec2f( 0, -1));
	p_H.pen.push_back(1); p_H.pos.push_back(ofVec2f( 1,  1));
	p_H.pen.push_back(1); p_H.pos.push_back(ofVec2f(-1,  0));
	patterns.push_back(p_H);
	
	
}
