#pragma once
#include "Arduino.h"

void blink(int);
String prettyTime(struct tm);
bool isSummer(struct tm);
double diffTime(String, String);
struct tm calcTomorrow(int month, int day, int year);
String formatHour(String str1);
