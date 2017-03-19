
#ifndef __St7920__
#define __St7920__

#include "Arduino.h"
#include "Print.h"

class St7920: public Print {
	private:
		uint8_t rs, rw, e, d7, d6, d5, d4;
		uint8_t currentMode;
		void sendBits(bool isData, bool isRead, uint8_t data);
		void sendPulse();
		void sendCommand(uint8_t command);
	public:
		St7920(uint8_t rs, uint8_t rw, uint8_t r, 
				uint8_t d7, uint8_t d6, uint8_t d5, uint8_t d4);
				
		void begin();
		
		// initialize basic mode
		// 4x8 chiniese characters or 4*16 ascii characters can be printed
		void basicMode();
		
		// initialize extended mode
		// screen can be used pixel by pixel in this mode
		void extendedMode();
		
		// moves cursor to first row firs col  and
		// fills RAM with 0x20 (ASCII code of space) in basic mode
		// cannot be used in extended mode
		void clear();
		
		// moves cursor to first row firs col in basic mode
		// cannot be used in extended mode
		void returnHome();
		
		// choose what you want after each character print in basic mode
		// true,  false: move cursor right [ DEFAULT MODE ]
		// false, false: move cursor left
		// true,  true : move content right
		// false, true : move content left
		void setEntryMode(bool right, bool scroll);
		
		// display control
		void control(bool displayOn, bool cursorOn, bool blinkOn);
		
		// move cursor position for next print in basic mode
		// true : move right
		// false: move left
		void moveCursor(bool right);
		
		// move content for 1 pixel in basic mode
		// true : move right
		// false: move left
		void moveContent(bool right);
		
		// St7920 has 4 custom 16x16 pixel character
		// They chan be changed with this method
		// charIdx: can be in [0, 3]
		// content: must be 16x2 array (8 rows, 2 columns)
		// (Be sure that vertical scroll is disabled in extended instruction!)
		// (This method can be used in basic mode)
		void setCustomChar(uint8_t charIdx, uint8_t content[][2]);
		
		// St7920 has 4 rows and 8 cols
		// you can print one chinese character, one custom character or
		// two ASCII caharacters in a cell.
		// row must be in [0, 3] and col must be in [0, 8]
		// (this method can be used in basic mode)
		void setCharacterCursor(uint8_t row, uint8_t col);
		
		// enables vertical scroll in extended mode
		// scroll must be disabled before character generation on basic mode
		void enableScroll();
		
		// disable vertical scroll in extended mode
		void disableScroll();
		
		// reverses pixels in given row in extended mode
		void reverseRow(uint8_t row);
		
		// sets vertical scroll position in extended mode
		// scrolling must be enabled with enableScroll()
		void setScrollPosition(uint8_t position);
		
		// sets cursor position in extended mode
		// row must be in [0, 63] and col in [0, 7]
		void setGraphicCursor(uint8_t row, uint8_t col);
		
		// in basic mode:
		// you should send two bytes.
		//   to print ASCII characters, send 2 ascii codes.
		//     ex: sendData('A'); sendData('Z');
		//     you can sent one byte to change first character,
		//     but you can't change just second character.
		//   to print custom characters (see setCustomChar) send 0x00.
		//   after 0x00,
		//     send 0x00 to print 1st custom character
		//     send 0x02 to print 2nd custom character
		//     send 0x04 to print 3rd custom character
		//     send 0x05 to print 4th custom character
		//   according to datasheet,
		//   to print characters in BIG5, send two bytes in [0xA140, 0xD75F]
		//   to print characters in GB, send two bytes in [0xA1A0, 0xF7FF]
		// in extended mode:
		//   you should send two bytes: 16 bits for current cursor position
		void sendData(uint8_t data1);
		
		virtual size_t write(uint8_t);
		using Print::write;
};

#endif
