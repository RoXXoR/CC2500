

#ifndef CC2500_h
#define CC2500_h

#include <SPI.h>
#include "cc2500_defines.h"

class CC2500 {
public:
	CC2500();
	void begin();
	uint8_t getChipVersion(); 

private:

	void writeRegister(uint8_t addr, uint8_t data);
	uint8_t readRegister(uint8_t addr);
	uint8_t readStatusRegister(uint8_t addr);

	void configureDeviceSettings();

};

#endif
