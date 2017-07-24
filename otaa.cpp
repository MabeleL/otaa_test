#include "Arduino.h"
#include <TheThingsNetwork.h>
#include <SoftwareSerial.h>

// Set your AppEUI and AppKey
//const char *appEui = "70B3D57EF000630E";
//const char *appKey = "DC02B9CD60F635CD719BE06DD9EDC792";
const char *appEui = "70B3D57EF0006580";
const char *appKey = "E3BE4704E797726880C0420C23179CFD";


SoftwareSerial loraSerial = SoftwareSerial(8, 7);


#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000)
    ;

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);
}

void loop()
{
  debugSerial.println("-- LOOP");

  // Prepare payload of 1 byte to indicate LED status
  byte payload[1];
  payload[0] = (digitalRead(LED_BUILTIN) == HIGH) ? 1 : 0;

  // Send it off
  ttn.sendBytes(payload, sizeof(payload));

  delay(10000);
}
