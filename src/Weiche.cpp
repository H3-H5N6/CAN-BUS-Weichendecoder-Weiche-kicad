#include "Weiche.h"

Weiche::Weiche(OutputControl &_g, OutputControl &_a, uint16_t _canAddr, uint16_t _dccAddr) : Debounce(), g(_g), a(_a), canAddr(_canAddr), dccAddr(_dccAddr) {
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
void Weiche::statusForCan(uint16_t (&data)[2][4]) {
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
  data[0][0] = canAddrGerade();
  switch (this->status()) {
    case WEICHE::POSITION::GERADE:
      data[0][1] = WEICHE::STATE::ON;
      break;
    case WEICHE::POSITION::RUNNING_GERADE:
      data[0][1] = WEICHE::STATE::RUNNING;
      break;
    case WEICHE::POSITION::UNKNOWN:
      data[0][1] = WEICHE::STATE::UNKNOWN_STATE;
      break;
    default:
      data[0][1] = WEICHE::STATE::OFF;
  }
  data[0][2] = current;
  data[0][3] = 0;

  // Abzweig
  data[1][0] = canAddrAbzweig();
  switch (this->status()) {
    case WEICHE::POSITION::ABZWEIG:
      data[1][1] = WEICHE::STATE::ON;
      break;
    case WEICHE::POSITION::RUNNING_ABZWEIG:
      data[1][1] = WEICHE::STATE::RUNNING;
      break;
    case WEICHE::POSITION::UNKNOWN:
      data[1][1] = WEICHE::STATE::UNKNOWN_STATE;
      break;
    default:
      data[1][1] = WEICHE::STATE::OFF;
  }
  data[1][2] = current;
  data[1][3] = 0;

  if (data[0][1] == WEICHE::STATE::RUNNING) {
    data[1][1] = WEICHE::STATE::BLOCKED_STATE;
  }
  if (data[1][1] == WEICHE::STATE::RUNNING) {
    data[0][1] = WEICHE::STATE::BLOCKED_STATE;
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
 * @brief Liefert true, wenn der Weiche die address zugeordnet ist, sonst false.
 *
 * @param address Weichenadresse
 * @return boolean true, wenn der Weiche die Adresse zugeordnet ist.
 */
boolean Weiche::find(uint16_t address) {
  if ((canAddrAbzweig() == address) || (canAddrGerade() == address)) {
    return true;
  }
  return false;
}

boolean Weiche::findDccAddr(uint16_t _dccAddr) {
  return (dccAddr == _dccAddr);
}

boolean Weiche::changeDcc(uint16_t _dccAddr, uint8_t direction) {
  if (findDccAddr(_dccAddr)) {
    if (direction == 0) {
      return change(canAddrGerade());
    } else {
      return change(canAddrAbzweig());
    }
  }
  return false;
}

/**
 * Ändert die Weichnstellung, falls der Weiche address zugeordnet ist.
 *
 * Liefert true, wenn die Weiche unter der jeweiligen Adresse erreichbar ist
 */
boolean Weiche::change(uint16_t address) {
  if ((canAddrAbzweig() != address) && (canAddrGerade() != address)) {
    return false;
  }
  // Wenn die Stellung der Weiche nicht geändert werden kann, wird sich die Adresse gemerkt und die Methode beendet.
  // Dies wird aber unterdrückt, wenn die gewüschte Stellung "in Arbeit ist"
  if (
      (status() == WEICHE::POSITION::RUNNING_GERADE && (address != canAddrGerade())) ||
      (status() == WEICHE::POSITION::RUNNING_ABZWEIG && (address != canAddrAbzweig()))) {
    if (this->nextAddress != address) {
      Serial.println("DEBUG WEICHE Set Nächste Adresse");
      this->nextAddress = address;
    }
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