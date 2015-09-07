//
//  Pointer.h
//  system03
//
//  Created by Ovis aries on 2015/08/28.
//
//

#ifndef __system03__Pointer__
#define __system03__Pointer__

#include "ofMain.h"
#define PHASE_POINTING 0
#define PHASE_IDLE 1

struct gridPattern
{
	deque<bool>	pen;
	vector<ofVec2f> pos;
};

class Pointer{
public:
	
	void init();
	void initPatterns();
	void update();
	void view();
	
	void goNextPoint();
	void goNextPattern(int manual = -1);
	
	bool getCurrentLaser();
	
	ofVec3f target;
	bool	laserState;
	
	int		phase;
	int		phaseCount;
	
	int		interval_point;
	int		interval_pattern;
	
	int		pattern_id;
	int		posIndex;
	int		loopCounter;
	float	Gridscale;
	
	vector<ofPtr<gridPattern> > patterns;
	
	gridPattern tmpPattern;
	void beginPattern();
	void addVertex(float x, float y, bool pen);
	void endPattern();
	
};

#endif /* defined(__system03__Pointer__) */