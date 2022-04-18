#include "Weiche.h"

Weiche::Weiche(OutputControl &_g, OutputControl &_a) : g(_g), a(_a) {
  this->gerade();
};

WEICHE::POSITION Weiche::gerade() {
  if (a.isOn()) {
    return WEICHE::POSITION::RUNNING_ABZWEIG;
  }
  if (g.isOn()) {
    return WEICHE::POSITION::RUNNING_GERADE;
  }
  postion = WEICHE::POSITION::RUNNING_GERADE;
  g.impulse();
  return WEICHE::POSITION::RUNNING_GERADE;
}

boolean Weiche::changeIsPosible() {
  return (a.isImpulePosible() && g.isImpulePosible());
}

WEICHE::POSITION Weiche::abzweig() {
  if (a.isOn()) {
    return WEICHE::POSITION::RUNNING_ABZWEIG;
  }
  if (g.isOn()) {
    return WEICHE::POSITION::RUNNING_GERADE;
  }
  postion = WEICHE::POSITION::RUNNING_ABZWEIG;
  a.impulse();
  return WEICHE::POSITION::RUNNING_ABZWEIG;
}

void Weiche::statusForCan(uint16_t (&data)[8]) {
  uint16_t current;
  switch (this->status()) {
    case WEICHE::POSITION::ABZWEIG:
    case WEICHE::POSITION::RUNNING_ABZWEIG:
      current = a.getAddress();
      break;
    case WEICHE::POSITION::GERADE:
    case WEICHE::POSITION::RUNNING_GERADE:
      current = g.getAddress();
      break;
  }

  // Gerade
  data[0] = g.getAddress();
  switch (this->status()) {
    case WEICHE::POSITION::GERADE:
      data[1] = WEICHE::STATE::ON;
      break;
    case WEICHE::POSITION::RUNNING_GERADE:
      data[1] = WEICHE::STATE::RUNNING;
      break;
    case WEICHE::POSITION::UNKNOWN:
      data[1] = WEICHE::STATE::UNKNOWN_STATE;
      break;
    default:
      data[1] = WEICHE::STATE::OFF;
  }
  data[2] = current;
  data[3] = 0;

  // Abzweig
  data[4] = a.getAddress();
  switch (this->status()) {
    case WEICHE::POSITION::ABZWEIG:
      data[5] = WEICHE::STATE::ON;
      break;
    case WEICHE::POSITION::RUNNING_ABZWEIG:
      data[5] = WEICHE::STATE::RUNNING;
      break;
    case WEICHE::POSITION::UNKNOWN:
      data[5] = WEICHE::STATE::UNKNOWN_STATE;
      break;
    default:
      data[5] = WEICHE::STATE::OFF;
  }
  data[6] = current;
  data[7] = 0;

  if (data[1] == WEICHE::STATE::RUNNING) {
    data[5] = WEICHE::STATE::BLOCKED_STATE;
  }
  if (data[5] == WEICHE::STATE::RUNNING) {
    data[1] = WEICHE::STATE::BLOCKED_STATE;
  }
}

uint16_t Weiche::statusAsAddress() {
  switch (this->status()) {
    case WEICHE::POSITION::ABZWEIG:
      return a.getAddress();
    case WEICHE::POSITION::GERADE:
      return g.getAddress();
    default:
      return 0;
  }
}

WEICHE::POSITION Weiche::status() {
  switch (postion) {
    case WEICHE::POSITION::ABZWEIG:
    case WEICHE::POSITION::GERADE:
    case WEICHE::POSITION::UNKNOWN:
      return postion;
    case WEICHE::POSITION::RUNNING_ABZWEIG:
      if (a.isOn()) {
        return postion;
      }
      return WEICHE::POSITION::ABZWEIG;
      break;
    case WEICHE::POSITION::RUNNING_GERADE:
      if (g.isOn()) {
        return postion;
      }
      return WEICHE::POSITION::GERADE;
      break;
    default:
      return WEICHE::POSITION::UNKNOWN;
  }
}

void Weiche::process() {
  g.process();
  a.process();

  // Übernimmt ggf. die letzte Adresse
  if (nextAddress != 0) {
    change(nextAddress);
  }
}

/**
 * Liefert true, wenn die Weiche unter der jeweiligen Adresse erreichbar ist
 */
boolean Weiche::change(uint16_t address) {
  if ((a.getAddress() != address) && (g.getAddress() != address)) {
    return false;
  }
  // Wenn die Stellung der Weiche nicht geändert werden kann, wird sich die Adresse gemerkt
  if (status() == WEICHE::POSITION::RUNNING_GERADE || status() == WEICHE::POSITION::RUNNING_ABZWEIG) {
    this->nextAddress = address;
    return true;
  }

  // Weiche kann gestellt werden, nextAddress wird gelöscht
  this->nextAddress = 0;

  // Weiche stellen
  if (a.getAddress() == address) {
    this->abzweig();
  }

  if (g.getAddress() == address) {
    this->gerade();
  }
  return true;
}