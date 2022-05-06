#include "Signal.h"

Signal::Signal(uint16_t _firstAddress, uint8_t _index, I2CSignal *_i2csignal, SIGNAL::SOCKET _socket) : firstAddress(_firstAddress), lastAddress(_firstAddress + 3), index(_index), i2csignal(_i2csignal), socket(_socket) {
  position = SIGNAL::POSITION::HP0;
  state = SIGNAL::STATE::SET;
}


boolean Signal::find(uint16_t _address) {
  if ((_address < firstAddress) || (_address > lastAddress)) {
    return false;
  }
  return true;
}

boolean Signal::change(uint16_t _address) {
  if ((_address < firstAddress) || (_address > lastAddress)) {
    return false;
  }

  switch (_address - firstAddress + 1) {  //  900,901,902,903 - 900 => 1 2 3 4
    case SIGNAL::POSITION::HP0:           // 1
      if (isHp0()) {
        return true;
      }
      position = SIGNAL::POSITION::HP0;
      state = SIGNAL::STATE::SET;
      break;
    case SIGNAL::POSITION::HP1:
      if (isHp1()) {
        return true;
      }
      position = SIGNAL::POSITION::HP1;
      state = SIGNAL::STATE::SET;
      break;

    case SIGNAL::POSITION::HP2:
      if (isHp2()) {
        return true;
      }
      position = SIGNAL::POSITION::HP2;
      state = SIGNAL::STATE::SET;
      break;
    case SIGNAL::POSITION::HP0SH1:
      if (isSh1()) {
        return true;
      }
      position = SIGNAL::POSITION::HP0SH1;
      state = SIGNAL::STATE::SET;
      break;
  }

  return true;
}

boolean Signal::isHp0() {
  if (position == SIGNAL::POSITION::HP0 && state == SIGNAL::STATE::POSITION_REACHED) {
    return true;
  }
  return false;
}

boolean Signal::isHp1() {
  if (position == SIGNAL::POSITION::HP1 && state == SIGNAL::STATE::POSITION_REACHED) {
    return true;
  }
  return false;
}

boolean Signal::isHp2() {
  if (position == SIGNAL::POSITION::HP2 && state == SIGNAL::STATE::POSITION_REACHED) {
    return true;
  }
  return false;
}

boolean Signal::isSh1() {
  if (position == SIGNAL::POSITION::HP0SH1 && state == SIGNAL::STATE::POSITION_REACHED) {
    return true;
  }
  return false;
}

void Signal::process() {
  if (state == SIGNAL::STATE::SET) {
    uint8_t value;
    switch (position) {
      case SIGNAL::POSITION::UNKNOWN:
      case SIGNAL::POSITION::HP0:
        value = i2csignal->getHP0(socket);
        break;
      case SIGNAL::POSITION::HP1:
        value = i2csignal->getHP1(socket);
        break;
      case SIGNAL::POSITION::HP2:
        value = i2csignal->getHP2(socket);
        break;
      case SIGNAL::POSITION::HP0SH1:
        value = i2csignal->getSH1(socket);
        break;
    }
    Serial.print(F("DEBUG I2C : i"));
    Serial.print(index);
    Serial.print(F(" v: 0x"));
    Serial.println(value, HEX);

    i2csignal->setNewState(value, index);
    i2csignal->writeState();
    state = SIGNAL::STATE::POSITION_REACHED;
  }
}