#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(NULL);
void setup() {
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false);
 delay(500);
 display.clearDisplay();
  display.setTextColor(WHITE);
 display.setCursor(0,0);
 display.println("TEST LINE 1");
 display.setCursor(50,10);
 display.println("TEST LINE 2");
 display.display();
 delay(2000);
}
void loop() {
 for (int i = 0; i < 8; i++) {
 display.clearDisplay();
 display.setCursor(5*i,8*i);
 display.println("TEST LINE 12345");
 display.display();
 delay(250);
 }
}