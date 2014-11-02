
// access types
#define CC2500_WRITE_SINGLE	0x00
#define CC2500_WRITE_BURST	0x40
#define CC2500_READ_SINGLE	0x80
#define CC2500_READ_BURST	0xC0
#define CC2500_READ_STATUS	0xC0


// configuration registers - keep content during sleep
#define CC2500_IOCFG2		0x00	// GDO2 Output Pin Configuration
#define CC2500_IOCFG1		0x01	// GDO1 Output Pin Configuration
#define CC2500_IOCFG0		0x02	// GDO0 Output Pin Configuration
#define CC2500_FIFOTHR		0x03	// RX FIFO and TX FIFO Thresholds
#define CC2500_SYNC		0x04	// Sync Word
#define CC2500_SYNC1		0x04	// Sync Word, High Byte
#define CC2500_SYNC0		0x05	// Sync Word, Low Byte
#define CC2500_PKTLEN		0x06	// Packet Length
#define CC2500_PKTCTRL1		0x07	// Packet Automation Control 1
#define CC2500_PKTCTRL0		0x08	// Packet Automation Control 0
#define CC2500_ADDR		0x09	// Device Address
#define CC2500_CHANNR		0x0A	// Channel Number
#define CC2500_FSCTRL1		0x0B	// Frequency Synthesizer Control 1
#define CC2500_FSCTRL0		0x0C	// Frequency Synthesizer Control 0
#define CC2500_FREQ		0x0D	// Frequency Control Word
#define CC2500_FREQ2		0x0D	// Frequency Control Word, High Byte
#define CC2500_FREQ1		0x0E	// Frequency Control Word, Middle Byte
#define CC2500_FREQ0		0x0F	// Frequency Control Word, Low Byte
#define CC2500_MDMCFG4		0x10	// Modem Configuration 4
#define CC2500_MDMCFG3		0x11	// Modem Configuration 3
#define CC2500_MDMCFG2		0x12	// Modem Configuration 2
#define CC2500_MDMCFG1		0x13	// Modem Configuration 1
#define CC2500_MDMCFG0		0x14	// Modem Configuration 0
#define CC2500_DEVIANT		0x15	// Modem Deviation Setting
#define CC2500_MCSM2		0x16	// Main Radio Control State Machine Configuration
#define CC2500_MCSM1		0x17	// Main Radio Control State Machine Configuration
#define CC2500_MCSM0		0x18	// Main Radio Control State Machine Configuration
#define CC2500_FOCCFG		0x19	// Frequency Offset Compensation Configuration
#define CC2500_BSCFG		0x1A	// Bit Synchronization Configuration
#define CC2500_AGCCTRL2		0x1B	// AGC Control 2
#define CC2500_AGCCTRL1		0x1C	// AGC Control 1
#define CC2500_AGCCTRL0		0x1D	// AGC Control 0
#define CC2500_WOREVT		0x1E	// Event0 Timeout	
#define CC2500_WOREVT1		0x1E	// Event0 Timeout, High Byte
#define CC2500_WOREVT0		0x1F	// Event0 TImeout, Low Byte
#define CC2500_WORCTRL		0x20	// Wake On Radio Control
#define CC2500_FREND1		0x21	// Front End RX Configuration
#define CC2500_FREND0		0x22	// Front End TX Configuration
#define CC2500_FSCAL3		0x23	// Frequency Synthesizer Calibration
#define CC2500_FSCAL2		0x24	// Frequency Synthesizer Calibration
#define CC2500_FSCAL1		0x25	// Frequency Synthesizer Calibration
#define CC2500_FSCAL0		0x26	// Frequency Synthesizer Calibration
#define CC2500_RCCTRL1		0x27	// RC Oscillator Configuration 1
#define CC2500_RCCTRL0		0x28	// RC Oscillator Configuration 0

// configuration registers - lose content during sleep
#define CC2500_FSTEST		0x29	// Frequency Synthesizer Calibration Control
#define CC2500_PTEST		0x2A	// Production Test
#define CC2500_AGCTEST		0x2B	// AGC Test
#define CC2500_TEST2		0x2C	// Various Test Settings 2
#define CC2500_TEST1		0x2D	// Various Test Settings 1
#define CC2500_TEST0		0x2E	// Various Test Settings 0

// status registers
#define CC2500_REG_PARTNUM	0x30	// PARTNUM – Chip ID
#define CC2500_REG_VERSION	0x31	// VERSION – Chip ID
#define CC2500_FREQEST		0x32	// Frequency Offset Estimate from Demodulator
#define CC2500_LQI		0x33	// Demodulator Estimate for Link Quality
#define CC2500_RSSI		0x34	// Received Signal Strength Indication
#define CC2500_MARCSTATE	0x35	// Main Radio Control State Machine State
#define CC2500_WORTIME1		0x36	// WOR Time, High Byte
#define CC2500_WORTIME0		0x37	// WOR Time, Low Byte
#define CC2500_PKTSTATUS	0X38	// Current GDOx Status and Packet Status
#define CC2500_VCO_VC_DAC	0x39	// Current Setting from PLL Calibration Module
#define CC2500_TXBYTES		0x3A	// Underflow and Number of Bytes
#define CC2500_RXBYTES		0x3B	// Overflow and Number of Bytes
#define CC2500_RCCTRL1_STATUS	0x3C	// Last RC Oscillator Calibration Result
#define CC2500_RCCTRL0_STATUS	0x3D	// Last RC Oscillator Calibration Result

#define CC2500_NUM_TXBYTES	0x7F	// Mask for TXBYTES status register
#define CC2500_NUM_RXBYTES	0x7F	// Mask for RXBYTES status register

// command strobes
#define CC2500_CMD_SRES		0x30	// Reset chip
#define CC2500_CMD_SFSTXON	0x31	// Enable and calibrate frequency synthesizer
#define CC2500_CMD_SXOFF	0x32	// Turn off crystal oscillator
#define CC2500_CMD_SCAL		0x33	// Calibrate frequency synthesizer and turn it off
#define CC2500_CMD_SRX		0x34	// Enable RX
#define CC2500_CMD_STX		0x35	// Enable TX
#define CC2500_CMD_SIDLE	0x36	// Exit Radio mode
#define CC2500_CMD_SWOR		0x38	// Start automatic RX polling
#define CC2500_CMD_SPWD		0x39	// Enter power down mode when CSn goes high.
#define CC2500_CMD_SFRX		0x3A	// Flush the RX FIFO buffer.
#define CC2500_CMD_SFTX		0x3B	// Flush the TX FIFO buffer.
#define CC2500_CMD_SWORRST	0x3C	// Reset real time clock
#define CC2500_CMD_SNOP		0x3D	// No operation. May be used to get access to the chip status byte.

// multi-byte registers
#define CC2500_PATABLE		0x3E	// power output table
#define CC2500_TX_FIFO		0x3F	// transmit FIFO
#define CC2500_RX_FIFO		0x3F	// receive FIFO
