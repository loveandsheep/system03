//
//  ofxKsmrRPiToL6470.cpp
//  system03
//
//  Created by Ovis aries on 2015/06/24.
//
//

#include "ofxKsmrRPiToL6470.h"

void ofxKsmrRPiToL6470::setup(bool callGPIOSetup, int numMotor)
{
	if (callGPIOSetup) gpio_init();
	gpio_configure(RPI_L6470_SS_PIN, GPIO_OUTPUT);
	
	motorFlg.assign(numMotor, false);
	
	numBits[RPI_L6470_SIG_ABSPOS]	= 22;
	numBits[RPI_L6470_SIG_ACCEL]	= 12;
	numBits[RPI_L6470_SIG_DECEL]	= 12;
	numBits[RPI_L6470_SIG_MAXSPEED]	= 10;
	numBits[RPI_L6470_SIG_MINSPEED] = 13;
	numBits[RPI_L6470_SIG_VOLT_HOLD]= 8;
	numBits[RPI_L6470_SIG_VOLT_RUN] = 8;
	numBits[RPI_L6470_SIG_VOLT_ACC] = 8;
	numBits[RPI_L6470_SIG_VOLT_DEC] = 8;
	numBits[RPI_L6470_SIG_STEPMODE] = 8;
	numBits[RPI_L6470_SIG_GOTO]		= 22;
	numBits[RPI_L6470_SIG_GOTO_INV] = 22;
	numBits[RPI_L6470_SIG_MOVE]		= 22;
	numBits[RPI_L6470_SIG_MOVE_INV] = 22;
	numBits[RPI_L6470_SIG_RUN]		= 20;
	numBits[RPI_L6470_SIG_RUN_INV]	= 20;
}

/* Signals */

void ofxKsmrRPiToL6470::sendSignal(unsigned char cmd, int val)
{
	sendSinglePacket(cmd, numBits[cmd], val);
}

void ofxKsmrRPiToL6470::setGo_toMult(int *pos, bool inverse)
{
	sendMultPacket(inverse ? 0x61 : 0x60, 22, pos);
}

/* SPI Sender */

void ofxKsmrRPiToL6470::sendSinglePacket(unsigned char cmd, int numBit, int val)
{
	std::vector<int> vals;
	vals.assign(motorFlg.size(), val);
	
	sendMultPacket(cmd, numBit, &val);
}

void ofxKsmrRPiToL6470::sendMultPacket(unsigned char cmd, int numBit, int *val)
{
	int numByte = numBit / 8;
	
	std::vector<unsigned char> sigs;
	sigs.assign((numByte + 1) * motorFlg.size(), 0x0);
	
	for (int i = 0;i < motorFlg.size();i++) sigs[i] = cmd;
	
	int cnt = motorFlg.size();
	for (int i = 0;i < numByte;i++)
	{
		for (int j = 0;j < motorFlg.size();j++)
		{
			unsigned char sendSig = (val[j] >> (8 * i)) & 0xFF;
			
			sigs[cnt] = motorFlg[j] ? sendSig : 0x00;
			cnt++;
		}
	}
	
	int count = 0;
	for (int j = 0;j < numByte + 1;j++){
		
		spiOpen();
		for (int i = 0;i < motorFlg.size();i++){
			sendSpi(sigs[j * motorFlg.size() + i]);
		}
		spiClose();
		
	}
}

void ofxKsmrRPiToL6470::spiOpen()
{
	gpio_clear(RPI_L6470_SS_PIN);
}

void ofxKsmrRPiToL6470::sendSpi(unsigned char sig)
{
	int r = spi->send1(sig);
	while (r < 0){
		spi->send1(sig);
		printf("retry sending");
	}
	usleep(100000);
}

void ofxKsmrRPiToL6470::spiClose()
{
	gpio_set(RPI_L6470_SS_PIN);
}

/* Motor SW */

void ofxKsmrRPiToL6470::enableMotor(int index)
{
	motorFlg[index] = true;
}

void ofxKsmrRPiToL6470::disableMotor(int index)
{
	motorFlg[index] = false;
}

void ofxKsmrRPiToL6470::enableAllMotor()
{
	for (int i = 0;i < motorFlg.size();i++) motorFlg[i] = true;
}

void ofxKsmrRPiToL6470::disableAllMotor()
{
	for (int i = 0;i < motorFlg.size();i++) motorFlg[i] = false;
}