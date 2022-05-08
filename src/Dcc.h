#ifndef DCC_H
#define DCC_H

#include <Arduino.h>
#include <NmraDcc.h>

#define DEBUG_DCC_MSG

NmraDcc Dcc;
DCC_MSG Packet;

#define DCC_PIN 2

// #define NOTIFY_DCC_MSG
struct CVPair {
  uint16_t CV;
  uint8_t Value;
};

CVPair FactoryDefaultCVs[] =
    {
        {CV_ACCESSORY_DECODER_ADDRESS_LSB, DEFAULT_ACCESSORY_DECODER_ADDRESS & 0xFF},
        {CV_ACCESSORY_DECODER_ADDRESS_MSB, DEFAULT_ACCESSORY_DECODER_ADDRESS >> 8}};

uint8_t FactoryDefaultCVIndex = 0;

void notifyCVResetFactoryDefault() {
  // Make FactoryDefaultCVIndex non-zero and equal to num CV's to be reset
  // to flag to the loop() function that a reset to Factory Defaults needs to be done
  FactoryDefaultCVIndex = sizeof(FactoryDefaultCVs) / sizeof(CVPair);
};

void notifyCVChange(uint16_t Addr, uint8_t Value) {
  Serial.print("notifyCVChange: ");
  Serial.print(Addr, DEC);
  Serial.print(',');
  Serial.println(Value, DEC);
}

/*
* Variante 2
* HP 0         41 + 0
* HP 1         41 + 1
* HP 2         42 + 1
* HP 0Sh1      42 + 0

* Variante 2
 * HP 0         42 + 0 | 41 + 0
 * HP 1         42 + 0 | 41 + 1
 * HP 2         41 + 1 | 42 + 1
 * HP 0+SH1     41 + 0 | 42 + 1
 */

// uint16_t can_addr_buffer[10][2];
uint8_t addrDebounce[10];
#define DEBUG_DCC
void notifyDccAccTurnoutOutput(uint16_t Addr, uint8_t Direction, uint8_t OutputPower) {
#ifdef DEBUG_DCC
  Serial.print("Address: ");
  Serial.print(Dcc.getAddr(), DEC);
  Serial.print(" notifyDccAccTurnoutOutput_neu: ");
  Serial.print(Addr, DEC);
  Serial.print(',');
  Serial.print(Direction, DEC);
  Serial.print(',');
  Serial.println(OutputPower, HEX);
#endif

  

  for (int i = 0; i < 5; i++) {
    if (weiche[i].findDccAddr(Addr)) {
      Serial.print(F("Find DCC-Address ["));
      Serial.print(Addr);
      Serial.print(F("] in Weiche ["));
      Serial.print(i);
      Serial.println(F("]"));
      uint8_t index = i*2 + Direction;
      if (OutputPower == 1 ){
        if (addrDebounce[index] == 0 ) {
          addrDebounce[index] = 1;
          weiche[i].changeDcc(Addr, Direction);
        } else {
          Serial.println("Ignore DCC Packet");
        }
      }
      if (OutputPower == 0 ){
           addrDebounce[index] = 0;
           Serial.println("Ignore DCC Packet");
      } 

    }
  }
  for (int i = 0; i < 6; i++) {
    if (signal[i].findDccAddr(Addr)) {
      Serial.print(F("Find DCC-Address ["));
      Serial.print(Addr);
      Serial.print(F("] in Signal ["));
      Serial.print(i);
      Serial.println(F("]"));
      signal[i].changeDcc(Addr, Direction);
    }
  }

  /*

    if ((Addr >= Dcc.getAddr()) && (Addr < Dcc.getAddr() + 5)) {
      uint16_t can_addr = 801 + ((Addr - 1) * 2 + Direction);

      //              (6 - 1)     * 2 + 0       -       6 -1           * 2
      //              (6 - 1)     * 2 + 1       -       6 -1           * 2
      //               10                       -        10                 = 0
      //               11                       -        10                 = 1
      byte index = ((Addr - 1) * 2 + Direction) - ((Dcc.getAddr() - 1) * 2);


      // [0] erfasst dem Wechsel 0 - > 1
      // [1] zu verabeitende can-Adresse, wird nach der Verabeitung zurückgesetzt

      if (can_addr_buffer[index][0] != can_addr) {
        if (OutputPower == 1) {
          can_addr_buffer[index][0] = can_addr;
          can_addr_buffer[index][1] = can_addr;

          Serial.print("Can-Addr: ");
          Serial.println(can_addr);
        }
      } else {
        if (OutputPower == 0) {
          can_addr_buffer[index][0] = 0;
        }
      }

      // Addr 1,0 -> 821
      // Addr 1,1 -> 822
    } else {
      Serial.println("Ignore");
    }*/
}

void init_DCC() {
  Serial.println("NMRA DCC");
#ifdef digitalPinToInterrupt
  Dcc.pin(DCC_PIN, 0);
#else
  Dcc.pin(0, DCC_PIN, 1);
#endif

  Dcc.init(MAN_ID_DIY, 10, CV29_ACCESSORY_DECODER | CV29_OUTPUT_ADDRESS_MODE, 0);
  Serial.println("NMRA DCC Init Done");
}

void dccWriteFactotyDefaults() {
  if (FactoryDefaultCVIndex && Dcc.isSetCVReady()) {
    FactoryDefaultCVIndex--;  // Decrement first as initially it is the size of the array
    uint16_t cv = FactoryDefaultCVs[FactoryDefaultCVIndex].CV;
    uint8_t val = FactoryDefaultCVs[FactoryDefaultCVIndex].Value;
#ifdef DEBUG_DCC_MSG
    Serial.print("loop: Write Default CV: ");
    Serial.print(cv, DEC);
    Serial.print(" Value: ");
    Serial.println(val, DEC);
#endif
    Dcc.setCV(cv, val);
  }
}

#endif