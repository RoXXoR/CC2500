

#include "CC2500.h"

CC2500::CC2500() {
}

void CC2500::begin() {
	SPI.begin();
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	
	digitalWrite(SS,HIGH);
	pinMode(SS,OUTPUT);
}

void CC2500::writeRegister(uint8_t addr, uint8_t data) {
	digitalWrite(SS,LOW);
	SPI.transfer(addr);
	SPI.transfer(data);
	digitalWrite(SS,HIGH);
}

uint8_t CC2500::readStatusRegister(uint8_t addr) {
	uint8_t recv;

	digitalWrite(SS,LOW);
	SPI.transfer(addr|CC2500_READ_BURST);
	recv = SPI.transfer(0x00);
	digitalWrite(SS,HIGH);
	return recv;
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
// CRC operation = (1) CRC calculation in TX and CRC check in RX enabled
// Forward Error Correction = (0) FEC disabled
// Length configuration = (1) Variable length packets, packet length configured by the first received byte after sync word.
// Packetlength = 255
// Preamble count = (2)  4 bytes
// Append status = 1
// Address check = (0) No address check
// FIFO autoflush = 0
// Device address = 0
// GDO0 signal selection = ( 6) Asserts when sync word has been sent / received, and de-asserts at the end of the packet
// GDO2 signal selection = (11) Serial Clock

}
uint8_t CC2500::getChipVersion() {
	return CC2500::readStatusRegister(CC2500_REG_VERSION);
}
