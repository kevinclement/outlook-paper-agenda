#include "CalendarItem.h"
#include "ConnectionManager.h"

ConnectionManager manager = ConnectionManager();

void setup() { 
  Serial.begin(115200);

  manager.connectToWifi();
  
  
}
 
void loop() {
}
