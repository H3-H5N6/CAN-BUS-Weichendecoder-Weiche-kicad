#include "Weiche.h"

Weiche::Weiche(OutputControl &_g, OutputControl &_a) : g(_g), a(_a){
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

boolean Weiche::changeIsPosible(){
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


uint16_t Weiche::statusAsAddress() {
  switch (this->status()){
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
            if (a.isOn()){
                return postion;
            }
            return WEICHE::POSITION::ABZWEIG;
            break;
        case WEICHE::POSITION::RUNNING_GERADE:
            if (g.isOn()){
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
}

void Weiche::change (uint16_t address) {
  if (a.getAddress() == address){
    this->abzweig();
  } else {
    if (g.getAddress() == address){
      this->gerade();
    } 
  }
}