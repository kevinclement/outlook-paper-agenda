#include "Utils.h"

void blink(int count) {
  for(int i=0; i<count; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
  }
}

String prettyTime(struct tm ts) {
  char buf[80];
  strftime(buf, sizeof(buf), "%A, %B %d", &ts);
  return String(buf);
}

String prettyTimeLong(struct tm ts) {
  char buf[80];
  strftime(buf, sizeof(buf), "%D %r", &ts);
  return String(buf);
}

String getBatteryPercentage() {
  float raw = analogRead(A13);
  float bat = (raw / 4095) * 2.0 * 3.3 * 1.1;
  int perc = (bat / 4.27) * 100;

  // > 4 means plugged in?
  // bat is 4.27

  Serial.print("bat is: ");
  Serial.println(bat);
  Serial.print("perc is: ");
  Serial.println(perc);

  return String(bat) + " : " + String(perc) + "%";
}

bool isSummer(struct tm ts)
{
  byte month = ts.tm_mon + 1;
  byte day = ts.tm_mday;
  byte hour = ts.tm_hour;
  byte weekday = ts.tm_wday + 1;

  // always false for Jan, Feb and Dec
  if ((month < 3) || (month > 11)) return false;

  // always true from Apr to Oct
  if ((month > 3) && (month < 11)) return true;

  // first sunday of current month
  int wd = (weekday + 1);
  uint8_t first_sunday = (7 + day - wd) % 7 + 1;

  // Starts at 2:00 am on the second sunday of Mar
  if (3 == month) {
      if (day < 7 + first_sunday) return false;
      if (day > 7 + first_sunday) return true;
      return (hour > 2);
  }

  // Ends a 2:00 am on the first sunday of Nov
  // We are only getting here if its Nov
  if (day < first_sunday) return true;
  if (day > first_sunday) return false;
  return (hour < 2);
}

double diffTime(String str1, String str2) {
    struct tm tm1;
    struct tm tm2;
    strptime(str1.c_str(), "%Y-%m-%dT%H:%M:%S", &tm1);
    strptime(str2.c_str(), "%Y-%m-%dT%H:%M:%S", &tm2);

    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);

    return difftime(t2, t1);
}

struct tm calcTomorrow(int month, int day, int year) {
    struct tm t;
    t.tm_year = year-1900;
    t.tm_mon = month - 1;
    t.tm_mday = day + 1;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    t.tm_isdst = -1;
    mktime(&t);

    return t;
}

// its late i know
String formatHour(String str1) {
  String fm = "";
  char buf[80];
  struct tm tm;
  strptime(str1.c_str(), "%Y-%m-%dT%H:%M:%S", &tm);

  int hour = tm.tm_hour > 12 ? tm.tm_hour - 12 : tm.tm_hour;
  fm += String(hour) + ":";

  strftime(buf, sizeof(buf), "%M %p", &tm);

  fm += String(buf);
  return fm;
}
