

#ifndef CC2500_h
#define CC2500_h

#include <SPI.h>
#include "cc2500_defines.h"

// defaults
#define DEVADDR	0x01
#define CHANNEL	0x00

class CC2500 {
public:
	CC2500();
	CC2500(uint8_t deviceAddress);
	CC2500(uint8_t deviceAddress, uint8_t channel);
	void begin();
	void setDeviceAddress(uint8_t deviceAddress);
	void setChannel(uint8_t channel);
	uint8_t getChipVersion(); 
	uint8_t getStatusByte(); 

private:
	uint8_t _channel;
	uint8_t _deviceAddress;

	void writeRegister(uint8_t addr, uint8_t data);
	void writeRegisterBurst(uint8_t saddr, uint8_t *data, uint8_t size);
	uint8_t readRegister(uint8_t addr);
	uint8_t readStatusRegister(uint8_t addr);
	void execStrobeCommand(uint8_t command);
	void resetDevice();
	void configureDeviceSettings();

};

#endif
