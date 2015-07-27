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
#include "geom_triangle.h"
#include "geom_rectangle.h"
#include "geom_hexagon.h"

class geomManager{
public:
	
	void setup();
	void update();
	
	void setScene(int num);
	ofVec3f getCurrentTargpos();
	bool	getCurrentLaser();
	
	ofPtr<baseGeometry> getCurrentScene(){return scenes[curScnIdx];}

	template<class T> void addScene()
	{
		ofPtr<baseGeometry> sc = ofPtr<baseGeometry>(new T);
		scenes.push_back(sc);
	}
	
protected:
	
	int curScnIdx;
	vector< ofPtr<baseGeometry> > scenes;

};

#endif /* defined(__system03__geomManager__) */
