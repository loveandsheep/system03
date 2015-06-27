//
//  ofxKsmrRPiToL6470.h
//  system03
//
//  Created by Ovis aries on 2015/06/24.
//
//

#ifndef __system03__ofxKsmrRPiToL6470__
#define __system03__ofxKsmrRPiToL6470__

#include <stdio.h>
#include <vector>
#include "ofxWiringPi.h"

#define RPI_L6470_SS_PIN 25
#define SPI_CHANNEL 0

#define RPI_L6470_SIG_ABSPOS		0x01
#define RPI_L6470_SIG_ACCEL			0x05
#define RPI_L6470_SIG_DECEL			0x06
#define RPI_L6470_SIG_MAXSPEED		0x07
#define RPI_L6470_SIG_MINSPEED		0x08
#define RPI_L6470_SIG_VOLT_HOLD		0x09
#define RPI_L6470_SIG_VOLT_RUN		0x0A
#define RPI_L6470_SIG_VOLT_ACC		0x0B
#define RPI_L6470_SIG_VOLT_DEC		0x0C
#define RPI_L6470_SIG_STEPMODE		0x16

#define RPI_L6470_SIG_GOTO			0x60
#define RPI_L6470_SIG_GOTO_INV		0x61
#define RPI_L6470_SIG_RUN			0x50
#define RPI_L6470_SIG_RUN_INV		0x51
#define RPI_L6470_SIG_MOVE			0x40
#define RPI_L6470_SIG_MOVE_INV		0x41

class ofxKsmrRPiToL6470{
public:
	
	void setup(bool callGPIOSetup, int numMotor);

	void enableMotor(int index);
	void disableMotor(int index);
	void enableAllMotor();
	void disableAllMotor();
	
	void sendSignal(unsigned char cmd, int val);
	
	void setGo_toMult	(int* pos, bool inverse = false);

protected:

	std::vector<bool> motorFlg;
	int numBits[0xFF];
	
	void sendSinglePacket(unsigned char cmd, int numBit, int val);
	void sendMultPacket(unsigned char cmd, int numBit, int* val);
	
	void sendSpi(unsigned char sig);
	void spiOpen();
	void spiClose();
	
	ofxWiringPi wpi;
};

#endif /* defined(__system03__ofxKsmrRPiToL6470__) */
