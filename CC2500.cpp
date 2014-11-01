

#include "CC2500.h"

CC2500::CC2500() {
	CC2500(DEVADDR, CHANNEL);
}
CC2500::CC2500(uint8_t deviceAddress) {
	CC2500(deviceAddress, CHANNEL);
}
CC2500::CC2500(uint8_t deviceAddress, uint8_t channel) {
	_deviceAddress = deviceAddress;
	_channel = channel;	
}

void CC2500::setDeviceAddress(uint8_t deviceAddress) {
	_deviceAddress = deviceAddress;
}

void CC2500::setChannel(uint8_t channel) {
	_channel = channel;
}

void CC2500::begin() {
	SPI.begin();
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	
	digitalWrite(SS,HIGH);
	pinMode(SS,OUTPUT);

	configureDeviceSettings();
}

void CC2500::writeRegister(uint8_t addr, uint8_t data) {
	digitalWrite(SS,LOW);
	SPI.transfer(addr);
	SPI.transfer(data);
	digitalWrite(SS,HIGH);
}

void writeRegisterBurst(uint8_t addr, uint8_t *data, uint8_t size) {
	digitalWrite(SS,LOW);
	SPI.transfer(addr);
	while (size > 0) {
		SPI.transfer(*data++);
		size--;
	}
	digitalWrite(SS,HIGH);
}

uint8_t CC2500::readRegister(uint8_t addr) {
	uint8_t recv;

	digitalWrite(SS,LOW);
	SPI.transfer(addr);
	recv = SPI.transfer(0x00);
	digitalWrite(SS,HIGH);
	return recv;
}

uint8_t CC2500::readStatusRegister(uint8_t addr) {
	return readRegister(addr|CC2500_READ_BURST);
}

void CC2500::configureDeviceSettings() {
// Crystal accuracy = 40 ppm
// X-tal frequency = 26 MHz
// RF output power = 0 dBm
// RX filterbandwidth = 540.000000 kHz
// Datarate = 250.000000 kbps
// Manchester enable = (0) Manchester disabled
// Optimization = Sensitivity
// Format of RX/TX data = (0) Normal mode, use FIFOs for RX and TX
// Forward Error Correction = (0) FEC disabled
// FIFO autoflush = 0
	
	CC2500::writeRegister(CC2500_IOCFG0, 0x06);		// GDO0	= sync word
	CC2500::writeRegister(CC2500_IOCFG2, 0x0B);		// GDO2 = serial clock
	CC2500::writeRegister(CC2500_PKTCTRL0, 0x05);		// variable packet length; CRC enabled
	CC2500::writeRegister(CC2500_PKTCTRL1, 0x05);		// addr. check enabled; status bytes appended
	CC2500::writeRegister(CC2500_PKTLEN, 0xFF);		// max. packet length
	CC2500::writeRegister(CC2500_ADDR, _deviceAddress);	// device address
	CC2500::writeRegister(CC2500_CHANNR, _channel);		// channel number
	CC2500::writeRegister(CC2500_FSCTRL1, 0x07);		// 
	CC2500::writeRegister(CC2500_FSCTRL0, 0x00);		// 
	CC2500::writeRegister(CC2500_FREQ2, 0x5D);		// RF frequency 2433.000000 MHz 
	CC2500::writeRegister(CC2500_FREQ1, 0x93);		// RF frequency 2433.000000 MHz
	CC2500::writeRegister(CC2500_FREQ0, 0xB1);		// RF frequency 2433.000000 MHz
	CC2500::writeRegister(CC2500_MDMCFG4, 0x2D);		// 
	CC2500::writeRegister(CC2500_MDMCFG3, 0x3B);		// data rate 250.000000 kbps
	CC2500::writeRegister(CC2500_MDMCFG2, 0x73);		// MSK; 30/32 sync mode
	CC2500::writeRegister(CC2500_MDMCFG1, 0x22);		// 2 bytes preamble
	CC2500::writeRegister(CC2500_MDMCFG0, 0xF8);		// channel spacing 199.9500 kHz
	CC2500::writeRegister(CC2500_DEVIANT, 0x00);		// modem deviation 0
	CC2500::writeRegister(CC2500_MCSM1, 0x3F);		// RX after RX or TX
	CC2500::writeRegister(CC2500_MCSM0, 0x18);		// 
	CC2500::writeRegister(CC2500_FOCCFG, 0x1D);		// 
	CC2500::writeRegister(CC2500_BSCFG, 0x1C);		//
	CC2500::writeRegister(CC2500_AGCCTRL2, 0xC7);		// 
	CC2500::writeRegister(CC2500_AGCCTRL1, 0x00);		// 
	CC2500::writeRegister(CC2500_AGCCTRL0, 0xB2);		// 
	CC2500::writeRegister(CC2500_FREND1, 0xB6);		// 
	CC2500::writeRegister(CC2500_FREND0, 0x10);		// 
	CC2500::writeRegister(CC2500_FSCAL3, 0xEA);		// 
	CC2500::writeRegister(CC2500_FSCAL2, 0x0A);		// 
	CC2500::writeRegister(CC2500_FSCAL1, 0x00);		// 
	CC2500::writeRegister(CC2500_FSCAL0, 0x11);		// 
}

uint8_t CC2500::getChipVersion() {
	return readStatusRegister(CC2500_REG_VERSION);
}

uint8_t CC2500::getStatusByte() {
	uint8_t recv;
	
	digitalWrite(SS,LOW);
	recv = SPI.transfer(CC2500_CMD_SNOP);
	digitalWrite(SS,HIGH);
	return recv;
}
