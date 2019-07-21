#pragma once

#include "JsonListener.h"
#include "CalendarItem.h"

class AgendaParser: public JsonListener {

  public:
    virtual void whitespace(char c);
    virtual void startDocument();
    virtual void key(String key);
    virtual void value(String value);
    virtual void endArray();
    virtual void endObject();
    virtual void endDocument();
    virtual void startArray();
    virtual void startObject();

    CalendarItem* getItems();
    int getTotalItemCount();
};
