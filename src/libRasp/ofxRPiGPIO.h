//
//  ofxRPiGPIO.h
//  system03
//
//  Created by Ovis aries on 2015/06/03.
//
//

#ifndef __system03__ofxRPiGPIO__
#define __system03__ofxRPiGPIO__

#define USE_GPIO
#ifdef USE_GPIO
#include "raspGPIO.h"
#endif

bool rpiGPIO_inited = false;

class ofxRPiGPIO{
public:
	
//#ifdef TARGET_LINUX_ARM
//#ifdef TARGET_OSX
	static void setup()
	{
		if (rpiGPIO_inited) return;
#ifdef USE_GPIO
		gpio_init();
#endif
		rpiGPIO_inited = true;
	}
	
	static void setPinMode(int pinNum, int gpio_inOut)
	{
#ifdef USE_GPIO
		gpio_configure(pinNum, gpio_inOut);
#endif
	}
	
	static void setPinValue(int numPin, bool digitalV)
	{
#ifdef USE_GPIO
		if (digitalV){
			printf("set high\n");
			gpio_set(numPin);
		}
		else
		{
			printf("set low\n");
			gpio_clear(numPin);
		}
#endif
	}
	
	static int	 getPinValue(int numPin)
	{
#ifdef USE_GPIO
		return gpio_read(numPin);
#endif 
		return 0;
	}
	
	static void setPullConf(int numPin, int gpio_pullxx)
	{
#ifdef USE_GPIO
		gpio_configure_pull(numPin, gpio_pullxx);
#endif
	}
	
//#else
	
//	void setup(){
////		cout << "func for RPi." << endl;
//	}
//	void setPinMode(int pinNum, int gpio_inOut){
////		cout << "Set pin " << pinNum << "to " << (gpio_inOut ? "OUT" : "IN") << endl;
//	}
//	void setPinValue(int numPin, bool digitalV){
////		cout << "Set pin " << numPin << "to " << (digitalV ? "HIGH" : "LOW") << endl;
//	}
//	int	 getPinValue(int numPin){return 0;}
	
//#endif
	
};

#endif /* defined(__system03__ofxRPiGPIO__) */
