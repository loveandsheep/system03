//
//  geom_rectangle.h
//  system03
//
//  Created by Ovis aries on 2015/07/21.
//
//

#ifndef system03_geom_rectangle_h
#define system03_geom_rectangle_h

#include "baseGeometry.h"

class geom_rectangle : public baseGeometry{
public:
	
	//	virtual void update();
	virtual void setup()
	{
		trail_speed = 0.003;
		trail_pos = 0.0;
		
		
		/*===== Path register =====*/
		float rad = 100.0;
		
		addPath(ofVec3f(0.0,0.0,0.0), false);
		for (int i = 0;i < 360 + 90;i+=90)
		{
			addPath(ofVec3f(cos(ofDegToRad(i - 90))*rad,
							sin(ofDegToRad(i - 90))*rad,0.0),
					i != 0);
		}
		addPath(ofVec3f(0.0,0.0,0.0), false);
	}
	
};

#endif
