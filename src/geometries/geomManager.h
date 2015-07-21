//
//  geomManager.h
//  system03
//
//  Created by Ovis aries on 2015/07/21.
//
//

#ifndef __system03__geomManager__
#define __system03__geomManager__

#include "ofMain.h"
#include "baseGeometry.h"

class geomManager{
public:
	
	void setup();
	void update();
	
	void setScene(int num);
	ofVec3f getCurrentTargpos();
	bool	getCurrentLaser();
	
	ofPtr<baseGeometry> getCurrentScene(){return scenes[curScnIdx];}
	
protected:
	
	int curScnIdx;
	vector< ofPtr<baseGeometry> > scenes;

};

#endif /* defined(__system03__geomManager__) */
