#include <Arduino.h>
#include "Display.h"
#include "CalendarItem.h"
#include "ConnectionManager.h"
#include "Utils.h"

#define uS_TO_S_FACTOR 1000000
// TODO: switch to 15 minutes (900)
#define TIME_TO_SLEEP  30        /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

void setup() {
  Serial.begin(115200);
  Serial.printf("Outlook ePaper Agenda by kevinc...\n");

  ++bootCount;

  pinMode(LED_BUILTIN, OUTPUT);
  blink(1);

  Display display = Display();
  display.init();

  // ConnectionManager manager = ConnectionManager();
  // manager.connectToWifi();

  // CalendarItem* items = manager.getItems(7, 23, 2019);
  // for (int i=0; i<manager.getTotalItemCount(); i++) {
  //   CalendarItem item = items[i];
  //   Serial.println(item.Subject);
  //   Serial.println("  LOC:   " + item.Location);
  //   Serial.println("  FB:    " + item.FreeBusy);
  //   Serial.println("  Start: " + item.Start);
  //   Serial.println("  End:   " + item.End);
  //   Serial.println();
  // }

  // blink to know i'm done
  blink(2);
  display.showItems(bootCount <= 1);
  delay(2000);
  display.showItems(false);
  delay(2000);
  display.showItems(false);

  // setup deep sleep and sleep the device
  // esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  // esp_deep_sleep_start();
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