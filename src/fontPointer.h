//
//  fontDrawer.h
//  system03
//
//  Created by Ovis aries on 2015/06/01.
//
//

#ifndef __system03__fontDrawer__
#define __system03__fontDrawer__

#include "ofMain.h"

class fontPointer{
public:
	
	void	setup(string path, float _scale, string viewStr);
	void	update();
	void	drawDebug();
	
	ofVec3f getPoint();
	void	setSentence(string viewStr);
	
	ofTrueTypeFont			font;
	vector<ofTTFCharacter>	sentence;
	ofVec2f					offset;
	float					scale;
	
	ofPath					path;
	vector<ofPolyline>		outlines;
	
	string					currentSentence;
	int						outlineCount;
	int						pathCount;
};

#endif /* defined(__system03__fontDrawer__) */
