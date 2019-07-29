#pragma once

#include "Arduino.h"

class CalendarItem {
  public:
    CalendarItem();

    String Subject;
    String FreeBusy;
    String Start;
    String StartFormatted;
    String End;
    String Location;
    String Runtime;

    void reset();

  private:

};
