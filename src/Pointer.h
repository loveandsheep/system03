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

struct gridPattern
{
	vector<bool>	pen;
	vector<ofVec2f> pos;
};

class Pointer{
public:
	
	void init();
	void initPatterns();
	void update();
	void view();
	
	bool getCurrentLaser();
	
	ofVec3f target;
	bool	laserState;
	
	int		pattern_id;
	int		posIndex;
	int		loopCounter;
	float	Gridscale;
	
	vector<gridPattern> patterns;
};

#endif /* defined(__system03__Pointer__) */