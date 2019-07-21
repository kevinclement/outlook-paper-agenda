#pragma once

#include "Arduino.h"

class CalendarItem {
  public:
    CalendarItem();

    String Subject;
    String FreeBusy;
    String Start;
    String End;
    String Location;

    void reset();

  private:

};
