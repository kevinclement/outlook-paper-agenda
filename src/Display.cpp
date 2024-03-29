#include "Display.h"
#include "CalendarItem.h"
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include "segoeuib7pt7b.h"
#include "segoeui9pt7b.h"
#include "segoeuib9pt7b.h"
#include "segoeui6pt7b.h"

GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT> display(GxEPD2_420(/*CS=*/ 26, /*DC=*/ 25, /*RST=*/ 21, /*BUSY=*/ 19));

Display::Display() {
}

void Display::init() {
  display.init(115200); 
  SPI.end(); // release standard SPI pins
  SPI.begin(5, 19, 18, 26);
}

const unsigned int header_height = 35;
void printHeader(String day) {

    // int16_t tbx, tby; uint16_t tbw, tbh;
    // display.getTextBounds("Kevin", 0, 0, &tbx, &tby, &tbw, &tbh);
    // Serial.printf("x:%d y:%d w:%d h:%d\n", tbx, tby, tbw, tbw);
    // Kevin = 35 x 35

    display.fillRect(0, 0, display.width(), header_height, GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);
    display.setCursor(5, 22);
    display.setFont(&segoeuib9pt7b);
    display.print(day);

    // TODO: use bounding text to properly calculate based on name variable
    // TODO: don't hardcode kevin
    display.setFont(&segoeui9pt7b);
    display.setCursor(display.width() - 48, 22);
    display.print("Kevin");
}

const unsigned int second_row_offset = 20;
void printRow(int y, String title, String start_time, String end_time, String location) {

  display.setCursor(5, y);
  display.setFont(&segoeuib7pt7b);
  display.print(start_time);
  display.setCursor(75, y);
  display.print(title);
  display.setFont(&segoeui6pt7b);
  display.setCursor(8, y + second_row_offset);
  display.print(end_time);
  display.setCursor(75, y + second_row_offset);
  display.print(location);

  // pad the right side a bit
  // TODO: calc font height, don't use fixed value
  display.fillRect(display.width() - 5, y-10, 15, 34, GxEPD_WHITE);

  // display.drawFastVLine(65, 4, 40, GxEPD_BLACK);
  // display.drawFastHLine(0, 55, 300, GxEPD_BLACK);
  // display.drawFastVLine(65, 64, 40, GxEPD_BLACK);
}

const unsigned int initial_row_offset = 55;
void printItems(CalendarItem* items, int totalItems) {
  display.setTextColor(GxEPD_BLACK);

  for (int i=0; i<totalItems; i++) {
    CalendarItem item = items[i];

    // Serial.println("  FB:    " + item.FreeBusy);
    // Serial.println("  Start: " + item.Start);
    // Serial.println("  End:   " + item.End);

    printRow(initial_row_offset + (i * 45), item.Subject, item.StartFormatted, item.Runtime, item.Location);
  }
}

void printFooter(String lastUpdate, String battery) {
  display.setFont(&segoeui6pt7b);
  display.setCursor(5, display.height() - 5);
  display.print(lastUpdate);
  display.setCursor(display.width() - 55, display.height() - 5);
  display.print(battery);
}

void Display::showItems(bool clear, String day, CalendarItem* items, int totalItems, String lastUpdate, String battery) {

  display.setRotation(1);
  display.setTextWrap(false);
  display.firstPage();
  //display.setPartialWindow(0, 0, display.width(), display.height());

  do {

    // BUG: something is causing the first header to be printed too low so
    // I have to put this tmp stuff here so its consistent
    if (clear) {
      display.fillScreen(GxEPD_WHITE);
      display.setTextColor(GxEPD_WHITE);
      display.setCursor(0, 0);
      display.setFont(&segoeuib7pt7b);
      display.print("NOOP");
    }

    printHeader(day);
    printItems(items, totalItems);
    printFooter(lastUpdate, battery);

  } while (display.nextPage());

  // turn it off now
  display.powerOff();
}