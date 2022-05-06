#include "Weiche.h"

Weiche::Weiche(OutputControl &_g, OutputControl &_a, uint16_t _canAddr, uint16_t _dccAddr) : g(_g), a(_a), canAddr(_canAddr), dccAddr(_dccAddr) {
  this->gerade();
};

uint16_t Weiche::canAddrGerade() {
  return canAddr + 1;
}

uint16_t Weiche::canAddrAbzweig() {
  return canAddr;
}

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

/**
 * @brief Weichenstatus als zwei CAN-Message
 * [0] ID für Gerade
 * [1] Status Gerade (0: nicht gerade, 1: Gerade, 2: running zu Gerade, 4 unbekannt)
 * [2] ID der aktuellen Position, identsich mit [6]
 * [3] 0
 * ---
 * [4] ID für Abzweig
 * [5] Status Abzweig (0: nicht abzweig, 1: Abzweig, 2: running zu Abzweig, 4 unbekannt)
 * [6] ID der aktuellen Position, identisch mit [2]
 * [7] 0
 *
 * @param Array für die Aufnahme des Weichenstatus
 */
void Weiche::statusForCan(uint16_t (&data)[8]) {
  uint16_t current;
  switch (this->status()) {
    case WEICHE::POSITION::ABZWEIG:
    case WEICHE::POSITION::RUNNING_ABZWEIG:
      current = canAddrAbzweig();
      break;
    case WEICHE::POSITION::GERADE:
    case WEICHE::POSITION::RUNNING_GERADE:
      current = canAddrGerade();
      break;
  }

  // Gerade
  data[0] = canAddrGerade();
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
  data[4] = canAddrAbzweig();
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

/**
 * @brief Liefert die ID der aktuellen Poistion.
 *
 * @return uint16_t ID der Position oder 0, wenn die Position unbekannt oder die Weiche sich noch bewegt.
 */
uint16_t Weiche::statusAsAddress() {
  switch (this->status()) {
    case WEICHE::POSITION::ABZWEIG:
      return canAddrAbzweig();
    case WEICHE::POSITION::GERADE:
      return canAddrGerade();
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
  if ((canAddrAbzweig() != address) && (canAddrGerade() != address)) {
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
  if (canAddrAbzweig() == address) {
    this->abzweig();
  }

  if (canAddrGerade() == address) {
    this->gerade();
  }
  return true;
}