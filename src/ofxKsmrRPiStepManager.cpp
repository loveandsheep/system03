//
//  ofxKsmrRPiStepManager.cpp
//  system03
//
//  Created by Ovis aries on 2015/06/01.
//
//

#include "ofxKsmrRPiStepManager.h"

void ofxKsmrRPiStepManager::setupRPi(bool callGPIOSetup)
{
	spi.init();
	if (callGPIOSetup) ofxRPiGPIO::setup();
#ifdef USE_GPIO
	ofxRPiGPIO::setPinMode(RPISTEP_SS, GPIO_OUTPUT);
#endif
}

void ofxKsmrRPiStepManager::sendSPIPacketAll(unsigned char *bytes, int length){
	
	int sigLength = steppers.size() * length;
	unsigned char signals[sigLength];
	
	for (int i = 0;i < sigLength;i+=steppers.size())
		for (int j = 0;j < steppers.size();j++)
			signals[i+j] = bytes[i];
	
	sendSPIMultiByte(signals, sigLength);
}

void ofxKsmrRPiStepManager::sendSPIPacketSelected(unsigned char *bytes, int length){
	
	int sigLength = steppers.size() * length;
	unsigned char signals[sigLength];
	
	for (int i = 0;i <  sigLength;i+=(2+steppers.size()))
		for (int j = 0;j < steppers.size();j++)
			if (steppers[j].sendEnable) signals[i+j] = bytes[i];
			else						signals[i+j] = 0x00;
	
	sendSPIMultiByte(signals, sigLength);
	
}

#pragma mark - implemented

void ofxKsmrRPiStepManager::sendSPIMultiByte(unsigned char *bytes, int length){
	spi_sendMulti(bytes, length);
}

void ofxKsmrRPiStepManager::sendSPIByteAll(unsigned char byte)
{
	unsigned char sig[steppers.size()];
	
	for (int i = 0;i < steppers.size();i++) sig[i] = byte;
	
	spi_sendMulti(sig, steppers.size());
}

void ofxKsmrRPiStepManager::sendSPIByteSelected(unsigned char byte)
{
	unsigned char sig[steppers.size()];
	
	for (int i = 0;i < steppers.size();i++){
		if (steppers[i].sendEnable) sig[i] = byte;
		else sig[i] = 0x0;
	}
	
	spi_sendMulti(sig, steppers.size());
}

void ofxKsmrRPiStepManager::sendSPIByteSingle(unsigned char byte, int ch){
	unsigned char sig[steppers.size()];
	
	for (int i = 0;i < steppers.size();i++){
		if (i == ch) sig[i] = byte;
		else sig[i] = 0x0;
	}
	
	spi_sendMulti(sig, steppers.size());
}

void ofxKsmrRPiStepManager::multi_go_to(int *pos){
	
	int signal_unitL = steppers.size();
	
	unsigned char signal[4*signal_unitL];
	unsigned char datas[steppers.size()][3];
	
	for (int i = 0;i < steppers.size();i++){
		
		int val = pos[i] * pow(2.0f,microStepInv);
		
		for (int j = 0;j < 3;j++){
			datas[i][j] = val & 0xFF;
			val = val >> 8;
		}
		
	}
	
	for (int i = 0;i < steppers.size();i++){
		signal[0*signal_unitL + i] = steppers[i].sendEnable ? 0x60 : 0x00;
		signal[1*signal_unitL + i] = steppers[i].sendEnable ? datas[i][2] : 0x00;
		signal[2*signal_unitL + i] = steppers[i].sendEnable ? datas[i][1] : 0x00;
		signal[3*signal_unitL + i] = steppers[i].sendEnable ? datas[i][0] : 0x00;
	}
	
	sendSPIMultiByte(signal, 4 * signal_unitL);
}

void ofxKsmrRPiStepManager::spi_sendMulti(unsigned char *bytes, int length){
	
	if (length % steppers.size() != 0) ofLogError("ksmrRPiStepper", "signal num is not corrent");
	
	int numBytes	= steppers.size();
	int numPacket	= length / steppers.size();
	
	for (int i = 0;i < numPacket;i++){
		
		spi_open();
		for (int j = 0;j < numBytes;j++){
			spi_send(bytes[i*numBytes+j]);
		}
		spi_close();
		
	}
	
}

#pragma mark TODO: implement RPi spiMethod
void ofxKsmrRPiStepManager::spi_open(){
#ifdef USE_GPIO
	ofxRPiGPIO::setPinValue(RPISTEP_SS, false);
#endif
}

void ofxKsmrRPiStepManager::spi_send(unsigned char sig){
	cout << "send 1byte";
	spi.send1(128);
	cout << "...Success" << endl;
}

void ofxKsmrRPiStepManager::spi_close(){
#ifdef USE_GPIO
	ofxRPiGPIO::setPinValue(RPISTEP_SS, true);
#endif
}