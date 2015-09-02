//
//  Console.h
//  system03
//
//  Created by Ovis aries on 2015/08/31.
//
//

#ifndef __system03__Console__
#define __system03__Console__

#include "ofMain.h"
#include "system03.h"
#include "Pointer.h"

class Console{
public:
	void init();
	void update();
	void view();
	
	ofFbo buffer;
	
	Pointer *pointPtr;
	system03 *sysPtr;
};

#endif /* defined(__system03__Console__) */
