#include "AgendaParser.h"
#include "JsonListener.h"
#include "CalendarItem.h"

String currentKey = "";
CalendarItem items[50]; // TODO: malloc (i sux at c++)
int total_items = 0;
int currentIndex = -1;


// Stuff I care about
//   Subject
//   FreeBusyType {Tentative, Free, Busy}
//   Start: "2019-07-22T11:30:00-07:00",
//   End: "2019-07-22T12:00:00-07:00",
//   Location\DisplayName: "Conf Room 32/31 (8)"

void AgendaParser::key(String key) {
  currentKey = key;
}

void AgendaParser::value(String value) {
  if (currentKey == "Subject") {
    items[++currentIndex] = CalendarItem();
    items[currentIndex].Subject = value;

    total_items++;
  }
  else if (currentKey == "DisplayName") {
    Serial.println("found: " + value);
    items[currentIndex].Location = value;
  }
}

CalendarItem* AgendaParser::getItems() {
  return items;
}

int AgendaParser::getTotalItemCount() {
  return total_items;
}


void AgendaParser::endArray() {}
void AgendaParser::endObject() {}
void AgendaParser::endDocument() {}
void AgendaParser::startArray() {}
void AgendaParser::startObject() {}
void AgendaParser::whitespace(char c) {}
void AgendaParser::startDocument() {}
