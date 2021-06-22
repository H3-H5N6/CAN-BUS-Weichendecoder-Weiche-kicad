#ifndef OUTPUT_CONTROL_H
#define OUTPUT_CONTROL_H

#include <Arduino.h>

// bit 0: LOW bzw HIGH bit 1: 0 aktiv LOW , 1 active HIGH
/** Namespace für die ENUMs */
namespace OUTPUT_CONTROL {

/** Unterschiedliche Modi eines Ausganges */
enum OUTPUT_MODE {
  /** Impuls */
  IMPULSE,
  /** Blinken, eingeshaltet */
  FLASH_ON,
  /** Blinken, ausgeschaltet */
  FLASH_OFF,
  /** wird permanat ein- bzw. ausgeschaltet */
  PERMANENT
};

/** Legt fest, ob der Azsgang LOW oder HIGHT-aktiv ist */
enum ACTIVE_MODE {
  /** EIN bei 0, aus bei 1 */
  low,
  /** EIN bei 1, aus bei 0 */
  high
};
}  // namespace OUTPUT_CONTROL

/** Einstellungen eines Ausgangs */
typedef struct {
  /** Modi des Ausgangs */
  OUTPUT_CONTROL::OUTPUT_MODE outputMode;
  /** Legt fest, ob der Ausgang LOW oder HIGHT-activ ist */
  OUTPUT_CONTROL::ACTIVE_MODE activeMode;
  /** Impullänge bei Impule bzw. Blinken */
  uint16_t duration;
  /** Zeit, ab der die nächste Aktion wieder möglich ist */
  uint16_t duration_2;
  /** Zeitpunkt der letzen Änderung in ms */
  unsigned long lastChanged;
  /** aktueller Zustand des Ausgang */
  boolean state;
  /** Pin des Ausgangs */
  byte pin;
} ACTOR;

class OutputControl {
 public:
  // OutputControl();

  explicit OutputControl(ACTOR *_actor);

  /**
   * 
   * @param outputMode 
   * @param activeMode legt fest, ober Ausgang aktiv LOW oder HIGHT ist
   * @param duration in ms für den outputMode impulse
   * @param pin
   */
  void init(OUTPUT_CONTROL::OUTPUT_MODE outputMode, OUTPUT_CONTROL::ACTIVE_MODE activeMode, uint16_t duration, byte pin);

  /**
   * Schaltet den Ausgang ein. 
   */
  void on();

  /**
   * Schaltet den Ausgang aus. 
   */
  void off();

  /**
   * Schaltet den Ausgang um. War er EIN, ist er anschließend AUS. War 
   * er AUS, ist er anschließend EIN
   */
  void toggle();

  /**
   * Schaltet den Augang zeitweise ein. Die Dauer wird mit duration bei init() fest.
   */
  void impulse();

  /**
   * Liefert true, wenn Ausgang auf EIN steht.
   */
  boolean isOn();

  /**
   * Liefert true, wenn der Ausgang AUS ist und das mindestens für die Dauer 
   * von mindestens duration_2 ms.
   */  
  boolean isImpulePosible();

  /**
   * Muss regelmäßig aufgerufen werden, damit bei der Nutzung vom impulse 
   * wieder ausgeschaltet werden
   */
  void process();

  /**
   * Schaltet das Blinken aus. Ist OUTPUT_CONTROL::OUTPUT_MODE nicht FLASH_OFF, passiert nichts.
   */
  void onFlash();

  /**
   * Schaltet da Blinken ein. Ist OUTPUT_CONTROL::OUTPUT_MODE nicht FLASH_ON, passiert nichts.
   */
  void offFlash();

 private:
  ACTOR *actor;

  /**
   * Schaltet zweitverzögert den Ausgang via toggle() wieder um. Die 
   * Zeitverzögerung wird wird mit duration bei init() festgelegt.
   */
  void flash();

  void writeState();
};

#endif