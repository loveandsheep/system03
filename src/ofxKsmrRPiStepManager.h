//
//  ofxKsmrRPiStepManager.h
//  system03
//
//  Created by Ovis aries on 2015/06/01.
//
//

#ifndef __system03__ofxKsmrRPiStepManager__
#define __system03__ofxKsmrRPiStepManager__

#include "ofxKsmrStepManager.h"
#include "ofxRPiGPIO.h"
#include "raspSPI.h"

#define RPISTEP_SS 25

class ofxKsmrRPiStepManager : public ofxKsmrStepManager{
public:
	
	void setupRPi();
	
	/*=== SPI Translate ===*/
	virtual void sendSPIPacketAll		(unsigned char* bytes,int length);
	virtual void sendSPIPacketSelected	(unsigned char* bytes,int length);
	
	virtual void sendSPIMultiByte	(unsigned char* bytes,int length);
	
	virtual void sendSPIByteAll		(unsigned char byte);
	virtual void sendSPIByteSingle	(unsigned char byte,int ch);
	virtual void sendSPIByteSelected(unsigned char byte);
	
	virtual void multi_go_to(int* pos);
	void spi_open();
	void spi_sendMulti(unsigned char *bytes, int length);
	void spi_send(unsigned char sig);
	void spi_close();
	
	SPI spi;
};


#endif /* defined(__system03__ofxKsmrRPiStepManager__) */
