#include "OutputControl.h"

// OutputControl::OutputControl() {}

OutputControl::OutputControl(OUTPUT_CONF *_configuration, uint16_t _address, byte _pin) {
  this->configuration = _configuration;
  this->address = _address;
  this->pin = _pin;

  // Ausgange "ausschalten" und state u. lastChange setzen
  switch (this->configuration->activeMode) {
    case OUTPUT_CONTROL::ACTIVE_MODE::low:
      pinMode(pin, INPUT_PULLUP);
      state = HIGH;
      break;
    case OUTPUT_CONTROL::ACTIVE_MODE::high:
      pinMode(pin, INPUT);
      state = LOW;
      break;
  }
  pinMode(pin, OUTPUT);
  lastChanged = millis();

  // Pause zwischen den Implsen definieren
  if (this->configuration->outputMode == OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE) {
    this->configuration->duration_2 = this->configuration->duration;
  } else {
    this->configuration->duration_2 = 0;
  }
}

void OutputControl::writeState() {
  Serial.print("Pin: ");
  Serial.print(pin);
  Serial.print(" State [");
  Serial.print(state);
  Serial.println("]");
  digitalWrite(pin, state);
}

boolean OutputControl::isImpulePosible() {
  Serial.print(lastChanged / 1000);
  Serial.print("-");
  Serial.print(this->configuration->duration / 1000);
  Serial.print("-");
  Serial.print(this->configuration->duration_2 / 1000);
  Serial.print("-");
  Serial.println(millis() / 1000);
  if (lastChanged == 0) {
    return true;
  }
  if (isOn()) {  // Bei Impulse ist der Ausgang aktiv
    return false;
  }
  if (lastChanged + this->configuration->duration + this->configuration->duration_2 > millis()) {
    // Serial.println("Noch nicht wieder frei");
    return false;
  }
  return true;
}

void OutputControl::on() {
  // Serial.println("on");
  if (this->configuration->outputMode != OUTPUT_CONTROL::OUTPUT_MODE::PERMANENT) {
    // return;
  }

  // Serial.print("active Mode: [");
  // Serial.print(this->actor->activeMode);
  // Serial.println("]");
  if (state == this->configuration->activeMode) {
    // Serial.println("Keine Änderung");
    return;
  }

  state = this->configuration->activeMode;
  lastChanged = millis();
  this->writeState();
}

void OutputControl::off() {
  // Serial.println("off");
  if (this->configuration->outputMode == OUTPUT_CONTROL::OUTPUT_MODE::PERMANENT) {
    // return;
  }

  // Serial.print("active Mode: [");
  // Serial.print(this->actor->activeMode);
  // Serial.println("]");
  if (state != this->configuration->activeMode) {
    return;
  }

  state = (!this->configuration->activeMode);
  if (this->configuration->outputMode != OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE) {
    lastChanged = millis();
  }
  this->writeState();
}

void OutputControl::toggle() {
  if (state == this->configuration->activeMode) {
    this->off();
  } else {
    this->on();
  }
}

void OutputControl::impulse() {
  // Serial.print("impulse: Mode: [");
  // Serial.print(this->actor->outputMode);
  // Serial.println("]");
  if (this->configuration->outputMode == OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE) {
    this->on();
  }
}

boolean OutputControl::isOn() {
  boolean result = (state == this->configuration->activeMode);
  return result;
}

void OutputControl::offFlash() {
  if (this->configuration->outputMode == OUTPUT_CONTROL::OUTPUT_MODE::FLASH_ON) {
    this->configuration->outputMode = OUTPUT_CONTROL::OUTPUT_MODE::FLASH_OFF;
  }
}

void OutputControl::onFlash() {
  if (this->configuration->outputMode == OUTPUT_CONTROL::OUTPUT_MODE::FLASH_OFF) {
    this->configuration->outputMode = OUTPUT_CONTROL::OUTPUT_MODE::FLASH_ON;
  }
}

void OutputControl::process() {
  if (this->configuration->outputMode == OUTPUT_CONTROL::OUTPUT_MODE::FLASH_ON) {
    this->flash();
  }

  if (this->configuration->outputMode == OUTPUT_CONTROL::OUTPUT_MODE::FLASH_OFF) {
    if (isOn()) {
      this->flash();
    }
  }

  if (this->configuration->outputMode == OUTPUT_CONTROL::OUTPUT_MODE::IMPULSE) {
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

  if (lastChanged + this->configuration->duration > millis()) {
    // Serial.println("Kein Umschalten");
    return;
  }

  // Serial.println("Umschalten");

  this->toggle();
}

uint16_t OutputControl::getAddress() {
  return address;
}
