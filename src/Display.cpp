#include "Display.h"
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

const char HelloWorld[] = "Hello World!";
void helloFullScreenPartialMode(int count)
{
    String text = HelloWorld;
  //Serial.println("helloFullScreenPartialMode");
  const char fullscreen[] = "full screen update";
  const char fpm[] = "fast partial mode";
  const char spm[] = "slow partial mode";
  const char npm[] = "no partial mode";
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.setRotation(1);
  display.setFont();
  display.setTextColor(GxEPD_BLACK);
  const char* updatemode;
  if (display.epd2.hasFastPartialUpdate)
  {
    Serial.println("Has hasFastPartialUpdate");
    updatemode = fpm;
  }
  else if (display.epd2.hasPartialUpdate)
  {
    Serial.println("Has hasPartialUpdate");
    updatemode = spm;
  }
  else
  {
    Serial.println("Has ELSE");
    updatemode = npm;
  }
  // do this outside of the loop
  int16_t tbx, tby; uint16_t tbw, tbh;
  // center update text
  display.getTextBounds(fullscreen, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t utx = ((display.width() - tbw) / 2) - tbx;
  uint16_t uty = ((display.height() / 4) - tbh / 2) - tby;
  // center update mode
  display.getTextBounds(updatemode, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t umx = ((display.width() - tbw) / 2) - tbx;
  uint16_t umy = ((display.height() * 3 / 4) - tbh / 2) - tby;
  // center HelloWorld
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t hwx = ((display.width() - tbw) / 2) - tbx;
  uint16_t hwy = ((display.height() - tbh) / 2) - tby;
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(hwx, hwy);
    display.print(text);
    display.setCursor(utx, uty);
    display.print(fullscreen);
    display.setCursor(umx, umy);
    display.print(updatemode);
  }
  while (display.nextPage());
  //Serial.println("helloFullScreenPartialMode done");
}

void printHeader(String day) {
    display.firstPage();

    int16_t tbx, tby; uint16_t tbw, tbh;
    display.getTextBounds("Kevin", 0, 0, &tbx, &tby, &tbw, &tbh);
    Serial.printf("x:%d y:%d w:%d h:%d\n", tbx, tby, tbw, tbw);
    // Kevin = 35 x 35

    int header_height = 35;
    do {
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
    } while (display.nextPage());
}

void printRow(int y, String title, String start_time, String end_time, String room) {
  const unsigned int second_row_offset = 20;
  do
  {
    display.setCursor(5, y);
    display.setFont(&segoeuib7pt7b);
    display.print(start_time);
    display.setCursor(70, y);
    display.print(title);
    display.setFont(&segoeui6pt7b);
    display.setCursor(5, y + second_row_offset);
    display.print(end_time);
    display.setCursor(70, y + second_row_offset);
    display.print(room);
    
    // display.drawFastVLine(65, 4, 40, GxEPD_BLACK);
    // display.drawFastHLine(0, 55, 300, GxEPD_BLACK);
    // display.drawFastVLine(65, 64, 40, GxEPD_BLACK);
  }
  while (display.nextPage());
}
void printItems() {
  display.setTextColor(GxEPD_BLACK);
  
  printRow(55, "Black Hat Content Development", "9:00 AM", "10:00 AM", "Conf Room 32/25");
  printRow(100, "OWA + WAC Sync", "1:00 PM", "2:00 PM", "32/3N");
}

void Display::showItems(bool clear, String day) {

  display.setRotation(1);
  //display.setPartialWindow(0, 0, display.width(), display.height());

  // BUG: something is causing the first header to be printed too low so
  // I have to put this tmp stuff here so its consistent
  if (clear) {
    display.firstPage();
    do {
        display.fillScreen(GxEPD_WHITE);
        display.setTextColor(GxEPD_WHITE);
        display.setCursor(0, 0);
        display.setFont(&segoeuib7pt7b);
        display.print("TMP");
    } while (display.nextPage());
  }

  printHeader(day);
  printItems();

  // turn it off now
  display.powerOff();
}