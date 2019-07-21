#include "CalendarItem.h"
#include "ConnectionManager.h"

ConnectionManager manager = ConnectionManager();

void setup() { 
  Serial.begin(115200);

  manager.connectToWifi();

  CalendarItem* items = manager.getItems(7, 23, 2019);
  for (int i=0; i<manager.getTotalItemCount(); i++) {
    CalendarItem item = items[i];
    Serial.println(item.Subject);
    Serial.println("  LOC:   " + item.Location);
    Serial.println("  FB:    " + item.FreeBusy);
    Serial.println("  Start: " + item.Start);
    Serial.println("  End:   " + item.End);
    Serial.println();
  }
}
 
void loop() {
}
