#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include "CalendarItem.h"
#include "ConnectionManager.h"
#include "segoeuib7pt7b.h"
#include "segoeui6pt7b.h"

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  30        /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT> display(GxEPD2_420(/*CS=*/ 26, /*DC=*/ 25, /*RST=*/ 21, /*BUSY=*/ 19));

void showBox2(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  display.setRotation(1);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.firstPage();
   
  // align with centered HelloWorld
  //display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  //uint16_t x = ((display.width() - tbw) / 2) - tbx;
  // height might be different
  //display.getTextBounds(HelloArduino, 0, 0, &tbx, &tby, &tbw, &tbh);
  //uint16_t y = ((display.height() / 4) - tbh / 2) - tby; // y is base line!
  // make the window big enough to cover (overwrite) descenders of previous text
  //uint16_t wh = FreeMonoBold9pt7b.yAdvance;
  //uint16_t wy = (display.height() / 4) - wh / 2;
  //display.setPartialWindow(0, wy, display.width(), wh);
  //display.firstPage();

  //display.drawRect(x, y - tbh, tbw, tbh, GxEPD_BLACK);
//    display.setCursor(x, y);
//    display.print(HelloArduino);

  do
  {
    display.fillScreen(GxEPD_WHITE);

    //display.drawRect(0, 0, 300, 70, GxEPD_BLACK);
    display.setCursor(5, 18);
    display.setFont(&segoeuib7pt7b);
    display.print("9:00 AM");
    display.setCursor(70, 18);
    display.print("Black Hat Content Development");
    display.setFont(&segoeui6pt7b);
    display.setCursor(5, 38);
    display.print("10:00 AM");
    display.setCursor(70, 38);    
    display.print("Conf Room 32/25");

    display.drawFastVLine(65, 4, 40, GxEPD_BLACK);
    display.drawFastHLine(0, 55, 300, GxEPD_BLACK);

    display.drawFastVLine(65, 64, 40, GxEPD_BLACK);
    display.setCursor(5, 80);
    display.setFont(&segoeuib7pt7b);
    display.print("1:00 PM");
    display.setCursor(70, 80);
    display.print("OWA + WAC Sync");
    display.setFont(&segoeui6pt7b);
    display.setCursor(5, 100);
    display.print("2:00 PM");
    display.setCursor(70, 100);    
    display.print("32/3N");

//    display.drawFastVLine(65, 4, 40, GxEPD_BLACK);
//    display.drawFastHLine(0, 55, 300, GxEPD_BLACK);
                    
    //display.fillRect(0, 0, 250, 20, GxEPD_BLACK);
    //display.fillRect(0, 30, 250, 20, GxEPD_BLACK);
  }
  while (display.nextPage());
}

void setup() {
  Serial.begin(115200);
  Serial.printf("Outlook ePaper Agenda by kevinc...\n");

  ++bootCount;

  pinMode(LED_BUILTIN, OUTPUT);

  for (int i=0; i<bootCount; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
  }

  display.init(115200); 
  SPI.end(); // release standard SPI pins
  SPI.begin(5, 19, 18, 26);

  ConnectionManager manager = ConnectionManager();

  manager.connectToWifi();

  CalendarItem* items = manager.getItems(7, 23, 2019);
  for (int i=0; i<manager.getTotalItemCount(); i++) {
    CalendarItem item = items[i];
    Serial.println(item.Subject);
    Serial.println("  LOC:   " + item.Location);
    Serial.println("  FB:    " + item.FreeBusy);
    Serial.println("  Start: " + item.Start);
    Serial.println("  End:   " + item.End);
    Serial.println();
  }

  // blink to know i'm done
  digitalWrite(LED_BUILTIN, HIGH);
  delay(300);
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);

  // helloWorld();
  // delay(1000);
  showBox2(16, 56, 48, 32);
  display.powerOff();

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

void loop() {

  // float raw = analogRead(A13);
  // float bat = (raw / 4095) * 2.0 * 3.3 * 1.1;

  // Serial.print("bat is: ");
  // Serial.println(bat);
  // digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  // delay(5000);                       // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  // delay(5000);                       // wait for a second
}