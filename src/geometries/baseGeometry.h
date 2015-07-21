//
//  baseGeometry.h
//  system03
//
//  Created by Ovis aries on 2015/07/21.
//
//

#ifndef __system03__baseGeometry__
#define __system03__baseGeometry__

#include "ofMain.h"

class baseGeometry{
public:
	virtual void setup(){}
	virtual void update();
	
	void		setupBasis();
	void		updateBasis();
	void		drawPath();
	
	void		addPath(ofVec3f p, bool laser);
	void		refleshLength();
	
	int			getInterpolateIndex(float pct);
	ofVec3f		getInterpolated(float pct);
	
	bool		targLaser;
	ofVec3f		targPos;
	
	float			trail_speed;
	float			trail_pos;
	
	float length_total;
	vector<float>			lengths;
	vector<ofVec3f>			path;
	vector<ofFloatColor>	color;
};

#endif /* defined(__system03__baseGeometry__) */
