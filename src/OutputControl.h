#ifndef OUTPUT_CONTROL_H
#define OUTPUT_CONTROL_H

#include <Arduino.h>

// bit 0: LOW bzw HIGH bit 1: 0 aktiv LOW , 1 active HIGH
namespace OUTPUT_CONTROL {
enum OUTPUT_MODE {
  IMPULSE,
  FLASH,
  PERMANENT
};
}

typedef struct {
  OUTPUT_CONTROL::OUTPUT_MODE outputMode;
  boolean activeMode;  // an bei LOW or HIGH
  uint16_t duration;   //
  unsigned long lastChanged;
  boolean state;
  byte pin;

} ACTOR;

class OutputControl {
 public:
  OutputControl(ACTOR *actor);

  void on();

  void off();

  void toggle();

  void pulse();

  

 private:
    ACTOR *actor;

    void writeState();
};

#endif