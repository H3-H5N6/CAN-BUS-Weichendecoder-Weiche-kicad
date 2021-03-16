#include "OutputControl.h"

OutputControl::OutputControl() {
  
}
OutputControl::OutputControl(ACTOR *_actor) {
  this->actor = _actor;
}

void OutputControl::init(OUTPUT_CONTROL::OUTPUT_MODE outputMode, OUTPUT_CONTROL::ACTIVE_MODE activeMode, uint16_t duration, byte pin) {
  unsigned long lastChanged = millis();

  boolean state;
  switch (activeMode) {
    case OUTPUT_CONTROL::ACTIVE_MODE::low:
      state = HIGH;
      break;
    case OUTPUT_CONTROL::ACTIVE_MODE::high:
      state = LOW;
      break;
  }

  this->actor->outputMode = outputMode;
  this->actor->activeMode = activeMode;
  this->actor->duration = duration;
  this->actor->lastChanged = lastChanged;
  this->actor->state = state;
  this->actor->pin = pin;

  // Ausgange "ausschalten"
  switch (activeMode) {
    case OUTPUT_CONTROL::ACTIVE_MODE::low:
      pinMode(pin, INPUT_PULLUP);
      break;
    case OUTPUT_CONTROL::ACTIVE_MODE::high:
      pinMode(pin, INPUT);
      break;
  }
  // Serial.print("PIN: ");
  // Serial.print(pin);
  // Serial.println(" Output");
  pinMode(pin, OUTPUT);
}

void OutputControl::writeState() {
  // Serial.print("Pin: ");
  // Serial.print(this->actor->pin);
  // Serial.print(" State [");
  // Serial.print(this->actor->state);
  // Serial.println("]");
  digitalWrite(this->actor->pin, this->actor->state);
}

void OutputControl::on() {
  // Serial.println("on");
  if (this->actor->outputMode != OUTPUT_CONTROL::OUTPUT_MODE::PERMANENT) {
    // return;
  }

  Serial.print("active Mode: [");
  Serial.print(this->actor->activeMode);
  Serial.println("]");
  if (this->actor->state == this->actor->activeMode) {
    Serial.println("Keine Änderung");
    return;
  }

  this->actor->state = this->actor->activeMode;
  this->actor->lastChanged = millis();
  this->writeState();
}

void OutputControl::off() {
  // Serial.println("off");
  if (this->actor->outputMode == OUTPUT_CONTROL::OUTPUT_MODE::PERMANENT) {
    // return;
  }

  // Serial.print("active Mode: [");
  // Serial.print(this->actor->activeMode);
  // Serial.println("]");
  if (this->actor->state != this->actor->activeMode) {
    return;
  }

  this->actor->state = (!this->actor->activeMode);
  this->actor->lastChanged = millis();
  this->writeState();
}

void OutputControl::toggle() {
  if (this->actor->state == this->actor->activeMode) {
    this->off();
  } else {
    this->on();
  }
}

void OutputControl::impulse() {
  // Serial.print("impulse: Mode: [");
  // Serial.print(this->actor->outputMode);
  // Serial.println("]");
  if (this->actor->outputMode == OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE) {
    this->on();
  }
}

boolean OutputControl::isOn() {
  boolean result = (this->actor->state == this->actor->activeMode);
  return result;
}

void OutputControl::process() {
  if (this->actor->outputMode == OUTPUT_CONTROL::OUTPUT_MODE::FLASH) {
    this->flash();
  }
  if (this->actor->outputMode == OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE) {
    if (isOn()) {
      this->flash();
    }
  }
}

void OutputControl::flash() {
  // Serial.print(this->actor->lastChanged);
  // Serial.print(" + ");
  // Serial.print(this->actor->duration);
  // Serial.print(" > ");
  // Serial.println(millis());

  if (this->actor->lastChanged + this->actor->duration > millis()) {
    // Serial.println("Kein Umschalten");
    return;
  }

  // Serial.println("Umschalten");

  this->toggle();
}