#include "St7920.h"

St7920 st7920(8, 9, 3, 7, 6, 5, 4);

void setup() {
  st7920.begin();
  st7920.extendedMode();
}

void loop() {
  for (uint8_t row = 0; row < 64; row++) {
    for (uint8_t col = 0; col < 8; col++) {
      st7920.setGraphicCursor(row, col);
      st7920.sendData(0);
      st7920.sendData(0);
    }
  }
  
  for (uint8_t row = 0; row < 64; row++) {
    for (uint8_t col = 0; col < 8; col++) {
      st7920.setGraphicCursor(row, col);
      st7920.sendData(0xFF);
      st7920.sendData(0xFF);
      delay(200);
    }
  }
}
