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
enum ACTIVE_MODE {
  low,
  high
};
}  // namespace OUTPUT_CONTROL

typedef struct {
  OUTPUT_CONTROL::OUTPUT_MODE outputMode;
  OUTPUT_CONTROL::ACTIVE_MODE activeMode;  // an bei LOW or HIGH
  uint16_t duration;   //
  unsigned long lastChanged;
  boolean state;
  byte pin;

} ACTOR;

class OutputControl {
 public:
  OutputControl(ACTOR *_actor);

  void init(OUTPUT_CONTROL::OUTPUT_MODE outputMode, OUTPUT_CONTROL::ACTIVE_MODE activeMode, uint16_t duration, byte pin);

  void on();

  void off();

  void toggle();

  void impulse();

  boolean isOn();

  void process();

 private:
  ACTOR *actor;

  void flash();

  void writeState();
};

#endif