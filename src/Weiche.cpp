#include "Weiche.h"

Weiche::Weiche(OutputControl _g, OutputControl _a) : g(_g), a(_a){};

WEICHE::POSITION Weiche::gerade() {
  if (a.isOn()) {
    return WEICHE::POSITION::RUNNING_ABZWEIG;
  }
  if (g.isOn()) {
    return WEICHE::POSITION::RUNNING_GERADE;
  }
  postion = WEICHE::POSITION::RUNNING_GERADE;
  g.impulse();
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