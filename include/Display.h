#pragma once

#include "Arduino.h"
#include "CalendarItem.h"

class Display {
  public:
    Display();
    void init();
    void showItems(bool,String,CalendarItem*,int);

  private:

};
