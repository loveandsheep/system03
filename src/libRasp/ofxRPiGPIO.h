//
//  ofxRPiGPIO.h
//  system03
//
//  Created by Ovis aries on 2015/06/03.
//
//

#ifndef __system03__ofxRPiGPIO__
#define __system03__ofxRPiGPIO__

#include "raspGPIO.h"

class ofxRPiGPIO{
public:
	
#ifdef TARGET_LINUX_ARM
//#ifdef TARGET_OSX
	
	void setup()
	{
		gpio_init();
	}
	
	void setPinMode(int pinNum, int gpio_inOut)
	{
		gpio_configure(pinNum, gpio_inOut);
	}
	
	void setPinValue(int numPin, bool digitalV)
	{
		if (digitalV)	gpio_set(numPin);
		else			gpio_clear(numPin);
	}
	
	int	 getPinValue(int numPin)
	{
		return gpio_read(numPin);
	}
	
	void setPullConf(int numPin, int gpio_pullxx)
	{
		gpio_configure_pull(numPin, gpio_pullxx);
	}
	
#else
	
	void setup(){
//		cout << "func for RPi." << endl;
	}
	void setPinMode(int pinNum, int gpio_inOut){
//		cout << "Set pin " << pinNum << "to " << (gpio_inOut ? "OUT" : "IN") << endl;
	}
	void setPinValue(int numPin, bool digitalV){
//		cout << "Set pin " << numPin << "to " << (digitalV ? "HIGH" : "LOW") << endl;
	}
	int	 getPinValue(int numPin){return 0;}
	
#endif
	
};

#endif /* defined(__system03__ofxRPiGPIO__) */
