#include "CalendarItem.h"
#include "ConnectionManager.h"

ConnectionManager manager = ConnectionManager();

void setup() { 
  Serial.begin(115200);

  manager.connectToWifi();

  CalendarItem* items = manager.getItems(7, 23, 2019);
  for (int i=0; i<manager.getTotalItemCount(); i++) {
    CalendarItem item = items[i];
    Serial.print("item: " + item.Subject + " loc: " + item.Location);
    Serial.println();
  }
}
 
void loop() {
}
