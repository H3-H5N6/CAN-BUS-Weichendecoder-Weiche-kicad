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

  boolean changeIsPosible();

  void process();

 private:
  OutputControl g;
  OutputControl a;
  WEICHE::POSITION postion = WEICHE::POSITION::UNKNOWN;
};

#endif
