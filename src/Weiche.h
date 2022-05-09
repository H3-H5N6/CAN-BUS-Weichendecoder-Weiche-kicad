#ifndef WEICHE_H

#define WEICHE_H

#include "Debounce.h"
#include "OutputControl.h"

namespace WEICHE {
enum POSITION : uint8_t {
  UNKNOWN,
  RUNNING_ABZWEIG,
  RUNNING_GERADE,
  ABZWEIG,
  GERADE
};

enum STATE : uint8_t {
  OFF,
  ON,
  RUNNING,
  BLOCKED_STATE,
  UNKNOWN_STATE
};

}  // namespace WEICHE

class Weiche : public Debounce {
 public:
  Weiche();
  Weiche(OutputControl &g, OutputControl &a, uint16_t canAddr, uint16_t dccAddr);

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

  void statusForCan(uint16_t (&data)[2][4]);

  boolean changeIsPosible();

  void process();

  boolean change(uint16_t address);
  boolean changeDcc(uint16_t _dcc_addr, uint8_t direction);
  boolean find(uint16_t address);
  boolean findDccAddr(uint16_t _dccAddr);

  uint16_t nextAddress;

 protected:
  uint8_t getDebounceMaske(uint16_t dccAddr, uint8_t direction) override;

 private:
  OutputControl g;
  OutputControl a;
  uint16_t canAddr;
  uint16_t dccAddress;
  WEICHE::POSITION postion = WEICHE::POSITION::UNKNOWN;
  uint16_t canAddrGerade();
  uint16_t canAddrAbzweig();
};

#endif
