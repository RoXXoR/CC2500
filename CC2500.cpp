

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
	_gdo0 = GDO0;	
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

	resetDevice();
	delay(100);
	configureDeviceSettings();
	execStrobeCommand(CC2500_CMD_SRX);
}

void CC2500::writeRegister(uint8_t addr, uint8_t data) {
	digitalWrite(SS,LOW);
	SPI.transfer(addr|CC2500_WRITE_SINGLE);
	SPI.transfer(data);
	digitalWrite(SS,HIGH);
}

void CC2500::writeRegisterBurst(uint8_t saddr, uint8_t *data, uint8_t size) {
	digitalWrite(SS,LOW);
	SPI.transfer(saddr|CC2500_WRITE_BURST);
	while (size > 0) {
		SPI.transfer(*data++);
		size--;
	}
	digitalWrite(SS,HIGH);
}

uint8_t CC2500::readRegister(uint8_t addr) {
	uint8_t recv;

	digitalWrite(SS,LOW);
	SPI.transfer(addr|CC2500_READ_SINGLE);
	recv = SPI.transfer(0x00);
	digitalWrite(SS,HIGH);
	return recv;
}

void CC2500::readRegisterBurst(uint8_t saddr, uint8_t *data, uint8_t size) {
	digitalWrite(SS,LOW);
	SPI.transfer(saddr|CC2500_READ_BURST);
	while (size > 0) {
		*data++ = SPI.transfer(0x00);
		size--;
	}
	digitalWrite(SS,HIGH);
}

void CC2500::execStrobeCommand(uint8_t command) {
	digitalWrite(SS,LOW);
	SPI.transfer(command);
	digitalWrite(SS,HIGH);
}

uint8_t CC2500::readStatusRegister(uint8_t addr) {
	return readRegister(addr|CC2500_READ_STATUS);
}

void CC2500::configureDeviceSettings() {
	uint8_t paTable[] = {0xFB};

	writeRegister(CC2500_IOCFG0, 0x06);		// GDO0	= sync word
	writeRegister(CC2500_IOCFG2, 0x0B);		// GDO2 = serial clock
	writeRegister(CC2500_PKTCTRL0, 0x05);		// variable packet length; CRC enabled
	writeRegister(CC2500_PKTCTRL1, 0x05);		// addr. check enabled; status bytes appended
	writeRegister(CC2500_PKTLEN, 0xFF);		// max. packet length
	writeRegister(CC2500_ADDR, _deviceAddress);	// device address
	writeRegister(CC2500_CHANNR, _channel);		// channel number
	writeRegister(CC2500_FSCTRL1, 0x07);		// 
	writeRegister(CC2500_FSCTRL0, 0x00);		// 
	writeRegister(CC2500_FREQ2, 0x5D);		// RF frequency 2433.000000 MHz 
	writeRegister(CC2500_FREQ1, 0x93);		// RF frequency 2433.000000 MHz
	writeRegister(CC2500_FREQ0, 0xB1);		// RF frequency 2433.000000 MHz
	writeRegister(CC2500_MDMCFG4, 0x2D);		// 
	writeRegister(CC2500_MDMCFG3, 0x3B);		// data rate 250.000000 kbps
	writeRegister(CC2500_MDMCFG2, 0x73);		// MSK; 30/32 sync mode
	writeRegister(CC2500_MDMCFG1, 0x22);		// 2 bytes preamble
	writeRegister(CC2500_MDMCFG0, 0xF8);		// channel spacing 199.9500 kHz
	writeRegister(CC2500_DEVIANT, 0x00);		// modem deviation 0
	writeRegister(CC2500_MCSM1, 0x3F);		// RX after RX or TX
	writeRegister(CC2500_MCSM0, 0x18);		// 
	writeRegister(CC2500_FOCCFG, 0x1D);		// 
	writeRegister(CC2500_BSCFG, 0x1C);		//
	writeRegister(CC2500_AGCCTRL2, 0xC7);		// 
	writeRegister(CC2500_AGCCTRL1, 0x00);		// 
	writeRegister(CC2500_AGCCTRL0, 0xB2);		// 
	writeRegister(CC2500_FREND1, 0xB6);		// 
	writeRegister(CC2500_FREND0, 0x10);		// 
	writeRegister(CC2500_FSCAL3, 0xEA);		// 
	writeRegister(CC2500_FSCAL2, 0x0A);		// 
	writeRegister(CC2500_FSCAL1, 0x00);		// 
	writeRegister(CC2500_FSCAL0, 0x11);		// 

	writeRegisterBurst(CC2500_PATABLE, paTable, sizeof(paTable));	
}

void CC2500::sendTxBuffer(uint8_t *txBuffer, uint8_t size) {
	uint8_t recv;

	writeRegisterBurst(CC2500_TX_FIFO, txBuffer, size);
	execStrobeCommand(CC2500_CMD_STX);
	delay(200);
	//while(digitalRead(_gdo0) == LOW);	// wait for the transfer to start
	//while(digitalRead(_gdo0) == HIGH);	// wait for the transfer to end

}

int8_t CC2500::receiveRxBuffer(uint8_t *rxBuffer, uint8_t size) {
	uint8_t pktLength;

	if (readStatusRegister(CC2500_RXBYTES)&CC2500_NUM_RXBYTES) {
		pktLength = readRegister(CC2500_RX_FIFO);
		readRegisterBurst(CC2500_RX_FIFO, rxBuffer, pktLength);
	} 
	return pktLength;
}

uint8_t CC2500::getChipVersion() {
	return readStatusRegister(CC2500_REG_VERSION);
}

uint8_t CC2500::getStatusByte() {
	uint8_t recv;
	
	digitalWrite(SS,LOW);
	recv = SPI.transfer(CC2500_CMD_SNOP|CC2500_READ_SINGLE);
	digitalWrite(SS,HIGH);
	return recv;
}

void CC2500::resetDevice() {
	execStrobeCommand(CC2500_CMD_SRES);
}
