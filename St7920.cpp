
#include "St7920.h"

#define BASIC_MODE 0
#define EXTENDED_MODE 1

// basic instructions
#define BI_CLEAR			0b00000001
#define BI_RETURN_HOME		0b00000010
#define BI_ENTRY_MODE_MASK	0b00000100 // see setEntryMode in header file
	#define BI_EM_RIGHT		0b00000010
	#define BI_EM_LEFT		0b00000000
	#define BI_EM_SCROLL_ON	0b00000001
#define BI_CONTROL_MASK		0b00001000
	#define BI_CM_DISPLAY_ON	0b00000100
	#define BI_CM_CURSOR_ON		0b00000010
	#define BI_CM_BLINK_ON		0b00000001
#define BI_MOVE_MASK		0b00010000
	#define BI_MM_CONTENT	0b00001000
	#define BI_MM_RIGHT		0b00000100

#define BI_FUNCTION_SET		0b00100000
#define BI_SET_CGRAM_ADDR	0b01000000
	#define CGRAM_ADDR_MASK	0b00110000
#define BI_SET_DDRAM_ADDR	0b10000000

// extended instructions
#define EI_FUNCTION_SET		0b00100000
	#define EI_FS_EXTENDED	0b00000100
	#define EI_FS_GRAPHIC	0b00000010
#define EI_SCROLL			0b00000010
	#define EI_SM_SCROLL_ON	0b00000001
#define EI_REVERSE			0b00000100
#define EI_SCROLL_ADDR		0b01000000
#define EI_GDRAM_ADDR		0b10000000

St7920::St7920(uint8_t rs, uint8_t rw, uint8_t e, 
		uint8_t d7, uint8_t d6, uint8_t d5, uint8_t d4) {
	this->rs = rs;
	this->rw = rw;
	this->e = e;
	this->d7 = d7;
	this->d6 = d6;
	this->d5 = d5;
	this->d4 = d4;
};

void St7920::begin() {
	pinMode(rs, OUTPUT);
	pinMode(rw, OUTPUT);
	pinMode(e, OUTPUT);
	pinMode(d7, OUTPUT);
	pinMode(d6, OUTPUT);
	pinMode(d5, OUTPUT);
	pinMode(d4, OUTPUT);
	
	basicMode();
}

void St7920::sendBits(bool isData, bool isRead, uint8_t data) {
	digitalWrite(e, LOW);
	digitalWrite(rw, isRead);
	digitalWrite(rs, isData);
	
	digitalWrite(d7, data & 0b10000000);
	digitalWrite(d6, data & 0b01000000);
	digitalWrite(d5, data & 0b00100000);
	digitalWrite(d4, data & 0b00010000);
	
	sendPulse();
	
	digitalWrite(d7, data & 0b00001000);
	digitalWrite(d6, data & 0b00000100);
	digitalWrite(d5, data & 0b00000010);
	digitalWrite(d4, data & 0b00000001);
	
	sendPulse();
}

void St7920::sendPulse() {
	if (currentMode == EXTENDED_MODE) {
		digitalWrite(e, HIGH);
		digitalWrite(e, LOW);
	} else {
		digitalWrite(e, HIGH);
		delayMicroseconds(80);
		digitalWrite(e, LOW);
		delayMicroseconds(80);
	}
}

void St7920::sendCommand(uint8_t command) {
	sendBits(LOW, LOW, command);
}

void St7920::basicMode() {
	sendCommand(BI_FUNCTION_SET);
	sendCommand(BI_FUNCTION_SET);
	currentMode = BASIC_MODE;
	control(true, false, false); // display on, cursor off, blink off
	clear();
	setEntryMode(true, false); // move cursor right, no scroll
}

void St7920::control(bool displayOn, bool cursorOn, bool blinkOn) {
	uint8_t cmd = BI_CONTROL_MASK;
	if (displayOn)
		cmd |= BI_CM_DISPLAY_ON;
	if (cursorOn)
		cmd |= BI_CM_CURSOR_ON;
	if (blinkOn)
		cmd |= BI_CM_BLINK_ON;
		
	sendCommand(cmd);
}

void St7920::extendedMode() {
	sendCommand(BI_FUNCTION_SET);
	sendCommand(BI_FUNCTION_SET | EI_FS_EXTENDED);
	currentMode = EXTENDED_MODE;
	sendCommand(EI_FUNCTION_SET | EI_FS_EXTENDED | EI_FS_GRAPHIC);
}

void St7920::enableScroll() {
	sendCommand(EI_SCROLL | EI_SM_SCROLL_ON);
}

void St7920::disableScroll() {
	sendCommand(EI_SCROLL);
}

void St7920::reverseRow(uint8_t row) {
	uint8_t cmd = EI_REVERSE | (row & 0x03);
	sendCommand(cmd);
}

void St7920::setScrollPosition(uint8_t position) {
	uint8_t cmd = EI_SCROLL_ADDR | (position & 0x3F);
	sendCommand(cmd);
}

void St7920::setGraphicCursor(uint8_t row, uint8_t col) {
	row &= 0x3F;
	col &= 0x07;
	
	if (row > 31) {
		row -= 32;
		col += 8;
	}

	uint8_t cmd = EI_GDRAM_ADDR | row;
	sendCommand(cmd);
	
	cmd = EI_GDRAM_ADDR | col;
	sendCommand(cmd);
}

void St7920::clear() {
	sendCommand(BI_CLEAR);
	delay(2); // datasheet says this command takes 1.6ms
}

void St7920::returnHome() {
	sendCommand(BI_RETURN_HOME);
}

void St7920::setEntryMode(bool right, bool scroll) {
	uint8_t cmd = BI_ENTRY_MODE_MASK;
	if (right)
		cmd |= BI_EM_RIGHT;
	if (scroll)
		cmd |= BI_EM_SCROLL_ON;
	
	sendCommand(cmd);
}

void St7920::moveCursor(bool right) {
	uint8_t cmd = BI_MOVE_MASK;
	if (right)
		cmd |= BI_MM_RIGHT;
		
	sendCommand(cmd);
}

void St7920::moveContent(bool right) {
	uint8_t cmd = BI_MOVE_MASK | BI_MM_CONTENT;
	if (right)
		cmd |= BI_MM_RIGHT;
		
	sendCommand(cmd);
}

void St7920::setCustomChar(uint8_t charIdx, uint8_t content[][2]) {
	uint8_t mask = BI_SET_CGRAM_ADDR;
	mask |= (charIdx << 4) & CGRAM_ADDR_MASK;
	sendCommand(mask);
	
	for (uint8_t row = 0; row < 16; row++)
		for (uint8_t col = 0; col < 2; col++)
			sendData(content[row][col]);
}

void St7920::setCharacterCursor(uint8_t row, uint8_t col) {
	// addresses:
	// 0x80 .. 0x87
	// 0x90 .. 0x97
	// 0x88 .. 0x8F
	// 0x98 .. 0x9F
	
	col = col & 0x07;
	row = row & 0x03;
	uint8_t data;
	
	data = 0x80 | ((row & 0x01) << 4);
	data |= (row & 0x02) << 2;
	data |= col;
	
	sendCommand(data);
}

void St7920::sendData(uint8_t data) {
	sendBits(HIGH, LOW, data);
}

inline size_t St7920::write(uint8_t value) {
  sendData(value);
  return 1;
}
