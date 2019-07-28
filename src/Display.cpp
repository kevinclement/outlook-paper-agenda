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

const char HelloWorld[] = "Hello World!";
void helloFullScreenPartialMode(int count)
{
    String text = HelloWorld + ' ' + count;
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

int count = 0;
void printHeader() {
    display.firstPage();
    do {
        display.setCursor(5, 18);
        display.setFont(&segoeuib7pt7b);
        display.print("KEVIN HEADER ");
        display.print(count);
    } while (display.nextPage());
}

void printItems() {
    
}

void Display::showItems(bool clear) {

  display.setRotation(1);
  // TODO: maybe later
  display.setPartialWindow(0, 0, display.width(), display.height());
  //display.setFullWindow();

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

  display.setTextColor(GxEPD_BLACK);
  printHeader();
  printItems();

  count++;

//    display.setFullWindow();
//   display.firstPage();

//   do
//   {
//     display.fillScreen(GxEPD_WHITE);

//     display.setCursor(5, 18);   
//     display.setFont(&segoeuib7pt7b);
//     display.print("9:00 AM");
//     display.setCursor(70, 18);
//     display.print("Black Hat Content Development");
//     display.setFont(&segoeui6pt7b);
//     display.setCursor(5, 38);
//     display.print("10:00 AM");
//     display.setCursor(70, 38);    
//     display.print("Conf Room 32/25");

//     display.drawFastVLine(65, 4, 40, GxEPD_BLACK);
//     display.drawFastHLine(0, 55, 300, GxEPD_BLACK);

//     display.drawFastVLine(65, 64, 40, GxEPD_BLACK);
//     display.setCursor(5, 80);
//     display.setFont(&segoeuib7pt7b);
//     display.print("1:00 PM");
//     display.setCursor(70, 80);
//     display.print("OWA + WAC Sync");
//     display.setFont(&segoeui6pt7b);
//     display.setCursor(5, 100);
//     display.print("2:00 PM");
//     display.setCursor(70, 100);
//     display.print("32/3N");
//   }
//   while (display.nextPage());

  // turn it off now
  display.powerOff();
}