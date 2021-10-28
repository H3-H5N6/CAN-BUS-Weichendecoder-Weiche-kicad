#ifndef WEICHE_H

#define WEICHE_H

#include "OutputControl.h"

namespace WEICHE {
enum POSITION {
  UNKNOWN,
  RUNNING_ABZWEIG,
  RUNNING_GERADE,
  ABZWEIG,
  GERADE
};

enum STATE {
  OFF,
  ON,
  RUNNING,
  BLOCKED_STATE,
  UNKNOWN_STATE
};

}

class Weiche {
 public:
  explicit Weiche(OutputControl &g, OutputControl &a);

  WEICHE::POSITION gerade();

  /**
   * Stellt die Weiche auf Abzweig.
   */
  WEICHE::POSITION abzweig();

  /**
   * Liefert die aktuelle Position aus Sicht der Software
   */
  WEICHE::POSITION status();

  uint16_t statusAsAddress();

  void statusForCan(uint16_t (&data)[8]);

  boolean changeIsPosible();

  void process();

  boolean change (uint16_t address); 

 private:
  OutputControl g;
  OutputControl a;
  WEICHE::POSITION postion = WEICHE::POSITION::UNKNOWN;
};

#endif
