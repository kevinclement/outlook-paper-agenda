#include "Display.h"
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include "segoeuib7pt7b.h"
#include "segoeui6pt7b.h"

GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT> display(GxEPD2_420(/*CS=*/ 26, /*DC=*/ 25, /*RST=*/ 21, /*BUSY=*/ 19));

Display::Display() {
}

void Display::init() {
  display.init(115200); 
  SPI.end(); // release standard SPI pins
  SPI.begin(5, 19, 18, 26);
}

void Display::showItems() {
  display.setRotation(1);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.firstPage();

  do
  {
    display.fillScreen(GxEPD_WHITE);

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
  }
  while (display.nextPage());

  // turn it off now
  display.powerOff();
}