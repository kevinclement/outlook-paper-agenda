#pragma once

#include "Arduino.h"
#include "CalendarItem.h"

class ConnectionManager {
  public:
    ConnectionManager();

    void connectToWifi();
    CalendarItem* getItems();
    
  private:
    String getBody(int, int, int);

};
