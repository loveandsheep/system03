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
#ifndef TARGET_OSX
	int speed = 5000;
	if ((wiringPiSPISetup (SPI_CHANNEL, speed)) < 0) {
		printf("wiringPiSPISetup error \n");
	}
	
	if (wiringPiSetupGpio() == -1)
	{
		printf("GPIO ERROR! \n");
	}
	pinMode(RPI_L6470_SS_PIN, OUTPUT);
	digitalWrite(RPI_L6470_SS_PIN, 1);
#endif
	
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
	numBits[RPI_L6470_SIG_MOVE]		= 22;
	numBits[RPI_L6470_SIG_MOVE_INV] = 22;
	numBits[RPI_L6470_SIG_RUN]		= 20;
	numBits[RPI_L6470_SIG_RUN_INV]	= 20;
	numBits[RPI_L6470_SIG_STOP_HARD]= 0;
	numBits[RPI_L6470_SIG_STOP_SOFT]= 0;
	verbose = false;
	
}

/* Signals */

void ofxKsmrRPiToL6470::resetDevice()
{
	enableAllMotor();
	sendSinglePacket(0x0,  0, 0x0);
	sendSinglePacket(0x0,  0, 0x0);
	sendSinglePacket(0x0,  0, 0x0);
	sendSinglePacket(0x0,  0, 0x0);
	sendSinglePacket(0xC0, 0, 0x0);
	disableAllMotor();
}

void ofxKsmrRPiToL6470::sendSignal(unsigned char cmd, int val)
{
	sendSinglePacket(cmd, numBits[cmd], val);
}

void ofxKsmrRPiToL6470::setGo_toMult(vector<int> val)
{
	std::vector<unsigned char> cmds;
	for (int i = 0;i < motorFlg.size();i++)
	{
		cmds.push_back(0x60);
//		if (val[i] < 0) val[i] = abs(val[i]) + 0x200000;
		val[i] = val[i] & 0x3FFFFF;
	}
	
	sendMultPacket(&cmds[0], 22, val);
}

/* SPI Sender */

void ofxKsmrRPiToL6470::sendSinglePacket(unsigned char cmd, int numBit, int val)
{
	std::vector<unsigned char> cmds;
	std::vector<int> vals;
	for (int i = 0;i < motorFlg.size();i++){
		cmds.push_back(cmd);
		vals.push_back(val);
	}
	
	sendMultPacket(&cmds[0], numBit, vals);
}

void ofxKsmrRPiToL6470::sendMultPacket(unsigned char* cmd, int numBit,vector<int> val)
{
	verbose = true;// (cmd[0] == RPI_L6470_SIG_ACCEL);
	int bitMask = powf(2, numBit) - 1;
	int numByte = numBit / 8;
	if (numBit % 8 > 0) numByte++;
		
	std::vector<unsigned char> sigs;
	for (int i = 0;i < (numByte + 1) * motorFlg.size();i++)
		sigs.push_back(0x00);
	
	for (int i = 0;i < motorFlg.size();i++) sigs[i] = motorFlg[i] ? cmd[i] : 0x0;
	
	int cnt = motorFlg.size();
	for (int i = 0;i < numByte;i++)
	{
		for (int j = 0;j < motorFlg.size();j++)
		{
			unsigned char sendSig = (val[j]  >> (8 * (numByte - i - 1))) &
									(bitMask >> (8 * (numByte - i - 1))) & 0xFF;
			
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
#ifndef TARGET_OSX
	digitalWrite(RPI_L6470_SS_PIN, 0);
#endif
	if (verbose) std::cout << "===Open===" << std::endl;
}

void ofxKsmrRPiToL6470::sendSpi(unsigned char sig)
{
	if (verbose) std::cout << std::hex << int(sig) << std::endl;
#ifndef TARGET_OSX
	wiringPiSPIDataRW(SPI_CHANNEL, &sig, 1);
#endif
	usleep(10);
}

void ofxKsmrRPiToL6470::spiClose()
{
#ifndef TARGET_OSX
	digitalWrite(RPI_L6470_SS_PIN, 1);
#endif
	if (verbose) std::cout << "===Close===" << std::endl;
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