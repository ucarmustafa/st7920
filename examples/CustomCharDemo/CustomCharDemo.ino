#include "St7920.h"

St7920 st7920(8, 9, 3, 7, 6, 5, 4);

void setup() {
  //Serial.begin(115200);
  st7920.begin();
  
  uint8_t hearth[16][2];
  hearth[ 0][0] = 0b00000000; hearth[ 0][1] = 0b00000000;
  hearth[ 1][0] = 0b00011100; hearth[ 1][1] = 0b01110000;
  hearth[ 2][0] = 0b01111110; hearth[ 2][1] = 0b11111100;
  hearth[ 3][0] = 0b11111110; hearth[ 3][1] = 0b11111110;
  hearth[ 4][0] = 0b11111111; hearth[ 4][1] = 0b11111110;
  hearth[ 5][0] = 0b11111111; hearth[ 5][1] = 0b11111110;
  hearth[ 6][0] = 0b11111111; hearth[ 6][1] = 0b11111110;
  hearth[ 7][0] = 0b01111111; hearth[ 7][1] = 0b11111100;
  hearth[ 8][0] = 0b01111111; hearth[ 8][1] = 0b11111100;
  hearth[ 9][0] = 0b00111111; hearth[ 9][1] = 0b11111000;
  hearth[10][0] = 0b00011111; hearth[10][1] = 0b11110000;
  hearth[11][0] = 0b00001111; hearth[11][1] = 0b11100000;
  hearth[12][0] = 0b00000111; hearth[12][1] = 0b11000000;
  hearth[13][0] = 0b00000011; hearth[13][1] = 0b10000000;
  hearth[14][0] = 0b00000001; hearth[14][1] = 0b00000000;
  hearth[15][0] = 0b00000000; hearth[15][1] = 0b00000000;

  uint8_t square[16][2];
  square[ 0][0] = 0b00000000; square[ 0][1] = 0b00000000;
  square[ 1][0] = 0b00000000; square[ 1][1] = 0b00000000;
  square[ 2][0] = 0b00111111; square[ 2][1] = 0b11111100;
  square[ 3][0] = 0b00111111; square[ 3][1] = 0b11111100;
  square[ 4][0] = 0b00111111; square[ 4][1] = 0b11111100;
  square[ 5][0] = 0b00111111; square[ 5][1] = 0b11111100;
  square[ 6][0] = 0b00111111; square[ 6][1] = 0b11111100;
  square[ 7][0] = 0b00111111; square[ 7][1] = 0b11111100;
  square[ 8][0] = 0b00111111; square[ 8][1] = 0b11111100;
  square[ 9][0] = 0b00111111; square[ 9][1] = 0b11111100;
  square[10][0] = 0b00111111; square[10][1] = 0b11111100;
  square[11][0] = 0b00111111; square[11][1] = 0b11111100;
  square[12][0] = 0b00111111; square[12][1] = 0b11111100;
  square[13][0] = 0b00111111; square[13][1] = 0b11111100;
  square[14][0] = 0b00000000; square[14][1] = 0b00000000;
  square[15][0] = 0b00000000; square[15][1] = 0b00000000;

  uint8_t diamond[16][2];
  diamond[ 0][0] = 0b00000000; diamond[ 0][1] = 0b00000000;
  diamond[ 1][0] = 0b00000001; diamond[ 1][1] = 0b00000000;
  diamond[ 2][0] = 0b00000011; diamond[ 2][1] = 0b10000000;
  diamond[ 3][0] = 0b00000111; diamond[ 3][1] = 0b11000000;
  diamond[ 4][0] = 0b00001111; diamond[ 4][1] = 0b11100000;
  diamond[ 5][0] = 0b00011111; diamond[ 5][1] = 0b11110000;
  diamond[ 6][0] = 0b00111111; diamond[ 6][1] = 0b11111000;
  diamond[ 7][0] = 0b01111111; diamond[ 7][1] = 0b11111100;
  diamond[ 8][0] = 0b00111111; diamond[ 8][1] = 0b11111000;
  diamond[ 9][0] = 0b00011111; diamond[ 9][1] = 0b11110000;
  diamond[10][0] = 0b00001111; diamond[10][1] = 0b11100000;
  diamond[11][0] = 0b00000111; diamond[11][1] = 0b11000000;
  diamond[12][0] = 0b00000011; diamond[12][1] = 0b10000000;
  diamond[13][0] = 0b00000001; diamond[13][1] = 0b00000000;
  diamond[14][0] = 0b00000000; diamond[14][1] = 0b00000000;
  diamond[15][0] = 0b00000000; diamond[15][1] = 0b00000000;

  uint8_t plus[15][2];
  plus[ 0][0] = 0b00000000; plus[ 0][1] = 0b00000000;
  plus[ 1][0] = 0b00000000; plus[ 1][1] = 0b00000000;
  plus[ 2][0] = 0b00000011; plus[ 2][1] = 0b11000000;
  plus[ 3][0] = 0b00000011; plus[ 3][1] = 0b11000000;
  plus[ 4][0] = 0b00000011; plus[ 4][1] = 0b11000000;
  plus[ 5][0] = 0b00000011; plus[ 5][1] = 0b11000000;
  plus[ 6][0] = 0b00111111; plus[ 6][1] = 0b11111100;
  plus[ 7][0] = 0b00111111; plus[ 7][1] = 0b11111100;
  plus[ 8][0] = 0b00111111; plus[ 8][1] = 0b11111100;
  plus[ 9][0] = 0b00111111; plus[ 9][1] = 0b11111100;
  plus[10][0] = 0b00000011; plus[10][1] = 0b11000000;
  plus[11][0] = 0b00000011; plus[11][1] = 0b11000000;
  plus[12][0] = 0b00000011; plus[12][1] = 0b11000000;
  plus[13][0] = 0b00000011; plus[13][1] = 0b11000000;
  plus[14][0] = 0b00000000; plus[14][1] = 0b00000000;
  plus[15][0] = 0b00000000; plus[15][1] = 0b00000000;

  st7920.setCustomChar(0, hearth);
  st7920.setCustomChar(1, square);
  st7920.setCustomChar(2, diamond);
  st7920.setCustomChar(3, plus);
}

void loop() {
  st7920.clear();
  
  for (int r = 0; r < 4; r++) {
    int c = r;
    //for (int c = 0; c < 8; c++) {
      st7920.setCharacterCursor(r, c);
      st7920.sendData(0);
      st7920.sendData(0);
      st7920.sendData(0);
      st7920.sendData(2);
      st7920.sendData(0);
      st7920.sendData(4);
      st7920.sendData(0);
      st7920.sendData(6);
      delay(200);
    //}
  }
}
