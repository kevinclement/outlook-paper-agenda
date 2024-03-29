#include <Arduino.h>
#include "Display.h"
#include "CalendarItem.h"
#include "ConnectionManager.h"
#include "Utils.h"

#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP  900        /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

void setup() {
  Serial.begin(115200);
  Serial.printf("Outlook ePaper Agenda by kevinc...\n");

  ++bootCount;

  pinMode(LED_BUILTIN, OUTPUT);
  blink(1);

  Display display = Display();
  display.init();

  ConnectionManager manager = ConnectionManager();
  manager.connectToWifi();
  struct tm ts = manager.getTime();

  CalendarItem* items = manager.getItems(
   ts.tm_mon + 1,
   ts.tm_mday,
   ts.tm_year + 1900,
   ts.tm_hour,
   ts.tm_min);
  //CalendarItem* items = manager.getItems(7, 29, 2019, 12, 0);
  int totalItems = manager.getTotalItemCount();
  Serial.printf("Found %d total items.\n", totalItems);
  for (int i=0; i<totalItems; i++) {
    CalendarItem item = items[i];
    Serial.println(item.Subject);
    Serial.println("  LOC:     " + item.Location);
    Serial.println("  FB:      " + item.FreeBusy);
    Serial.println("  Start:   " + item.Start);
    Serial.println("  End:     " + item.End);
    Serial.println("  Start F: " + item.StartFormatted);
    Serial.println("  Runtime: " + item.Runtime);

    Serial.println();
  }

  // blink to know i'm done
  blink(2);

  display.showItems(bootCount <= 1, prettyTime(ts), items, totalItems, prettyTimeLong(ts), getBatteryPercentage());

  // setup deep sleep and sleep the device
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

void loop() {
}