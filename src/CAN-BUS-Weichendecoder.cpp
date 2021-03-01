#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(10);

void setup() {
  // while (!Serial)
  //   ;
  // Serial.begin(115200);

  //mcp2515.reset();
  //mcp2515.setBitrate(CAN_125KBPS);
  //mcp2515.setNormalMode();
  //mcp2515.
  //Serial.println("Example: Write to CAN");

  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
