#pragma once
#include "Arduino.h"

void blink(int);
String prettyTime(struct tm);
String prettyTimeLong(struct tm);
bool isSummer(struct tm);
double diffTime(String, String);
struct tm calcTomorrow(int month, int day, int year);
String getBatteryPercentage();
String formatHour(String str1);
