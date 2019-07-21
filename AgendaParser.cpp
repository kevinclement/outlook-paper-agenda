#include "AgendaParser.h"
#include "JsonListener.h"

bool nextValue = false;

void ExampleListener::whitespace(char c) {
  //Serial.println("whitespace");
}

void ExampleListener::startDocument() {
  //Serial.println("start document");
}

void ExampleListener::key(String key) {
  //Serial.println("key: " + key);
  if (key == "Subject") 
  {
    nextValue = true;
  } else {
    nextValue = false;
  }
  
}

void ExampleListener::value(String value) {
  if (nextValue) {
    Serial.println("subject: " + value);
  }
  
  //Serial.println("value: " + value);
}

void ExampleListener::endArray() {
  //Serial.println("end array. ");
}

void ExampleListener::endObject() {
  //Serial.println("end object. ");
}

void ExampleListener::endDocument() {
  //Serial.println("end document. ");
}

void ExampleListener::startArray() {
   //Serial.println("start array. ");
}

void ExampleListener::startObject() {
   //Serial.println("start object. ");
}
