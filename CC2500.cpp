

#include "CC2500.h"

CC2500::CC2500() {
	CC2500(DEVADDR, CHANNEL);
}
C2500::CC2500(uint8_t deviceAddress) {
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
// Deviation = 0.000000
// Return state:  Return to RX state upon leaving either TX or RX
// Datarate = 250.000000 kbps
// Modulation = (7) MSK
// Manchester enable = (0) Manchester disabled
// RF Frequency = 2433.000000 MHz
// Channel spacing = 199.950000 kHz
// Channel number = 0
// Optimization = Sensitivity
// Sync mode = (3) 30/32 sync word bits detected
// Format of RX/TX data = (0) Normal mode, use FIFOs for RX and TX
// Forward Error Correction = (0) FEC disabled
// Preamble count = (2)  4 bytes
// FIFO autoflush = 0
// Device address = 0
	
	CC2500::writeRegister(CC2500_IOCFG0, 0x06);		// GDO0	= sync word
	CC2500::writeRegister(CC2500_IOCFG2, 0x0B);		// GDO2 = serial clock
	CC2500::writeRegister(CC2500_PKTCTRL0, 0x05);		// variable packet length; CRC enabled
	CC2500::writeRegister(CC2500_PKTCTRL1, 0x05);		// addr. check enabled; status bytes appended
	CC2500::writeRegister(CC2500_PKTLEN, 0xFF);		// max. packet length
	CC2500::writeRegister(CC2500_ADDR, _deviceAddress);	// device address
	CC2500::writeRegister(CC2500_CHANNR, _channel);		// channel number
}

uint8_t CC2500::getChipVersion() {
	return readStatusRegister(CC2500_REG_VERSION);
}
