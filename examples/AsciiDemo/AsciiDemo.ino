#include "St7920.h"


St7920 st7920(8, 9, 3, 7, 6, 5, 4);


void setup() {
  st7920.begin();
	
}

void loop() {
  st7920.setCharacterCursor(0, 0);
  st7920.print("ST7920 Demo");
  
  st7920.setCharacterCursor(1, 0);
  st7920.print("ucarmustafa.com");

  st7920.setCharacterCursor(3, 0);
  st7920.print("Nums: ");

  for (char i = '0'; i <= '9'; i++)
    st7920.print(i);
    
  delay(1000);
}
