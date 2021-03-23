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
  Weiche(OutputControl g, OutputControl a);

  WEICHE::POSITION gerade();

  WEICHE::POSITION abzweig();

  WEICHE::POSITION status();

  boolean changeIsPosible();

 private:
  OutputControl g;
  OutputControl a;
  WEICHE::POSITION postion = WEICHE::POSITION::UNKNOWN;
};

#endif