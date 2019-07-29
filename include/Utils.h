#pragma once
#include "Arduino.h"

void blink(int);
String prettyTime(struct tm);
bool isSummer(struct tm);
double diffTime(String, String);
String formatHour(String str1);
