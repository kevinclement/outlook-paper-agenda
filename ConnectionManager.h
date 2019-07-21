#pragma once

#include "Arduino.h"
#include "CalendarItem.h"

class ConnectionManager {
  public:
    ConnectionManager();

    void connectToWifi();
    CalendarItem* getItems();
    int getTotalItemCount();
    
  private:
    String getBody(int, int, int);

};
