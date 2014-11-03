

#ifndef CC2500_h
#define CC2500_h

#include <SPI.h>
#include "cc2500_defines.h"

// defaults
#define DEVADDR	0x00
#define CHANNEL	0x00
#define GDO0	13	// P2.6 on MSP430F2274 on RF2500T	

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
	
	void sendTxBuffer(uint8_t *txBuffer, uint8_t size);
	int8_t receiveRxBuffer(uint8_t *rxBuffer, uint8_t size);


//private:
	uint8_t _channel;
	uint8_t _deviceAddress;
	uint8_t _gdo0;

	void writeRegister(uint8_t addr, uint8_t data);
	void writeRegisterBurst(uint8_t saddr, uint8_t *data, uint8_t size);
	uint8_t readRegister(uint8_t addr);
	void readRegisterBurst(uint8_t saddr, uint8_t *data, uint8_t size);
	uint8_t readStatusRegister(uint8_t addr);
	void execStrobeCommand(uint8_t command);
	void resetDevice();
	void configureDeviceSettings();

};

#endif
