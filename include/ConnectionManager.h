#pragma once

#include "Arduino.h"
#include "CalendarItem.h"

class ConnectionManager {
  public:
    ConnectionManager();

    void connectToWifi();
    struct tm getTime();
    CalendarItem* getItems(int, int, int, int, int);
    int getTotalItemCount();
    
  private:
    String getBody(int, int, int, int, int);

};
