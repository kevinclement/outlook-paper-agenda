#include "Utils.h"

void blink(int count) {
  for(int i=0; i<count; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
  }
}

