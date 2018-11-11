// Lora Radio Setup
#include <RH_RF95.h>
#include <avr/interrupt.h> //watchdog timer
#include <avr/wdt.h>
#include <EEPROM.h>


#include <Arduino.h>
#include <CloudIoTCore.h>
#include <CloudIoTCoreMQTTClient.h>
#include "device_1_config.h"

// Software serial
#include <SoftwareSerial.h>
SoftwareSerial SerialAT(13, 12); // RX, TX

#define FREQUENCY  434
#define LED        15 // Moteino MEGAs have LEDs on D15
#define FLASH_SS   23 // and FLASH SS on D23
// Singleton instance of the radio driver
RH_RF95 rf95;

// GSM configuration
#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>
const char apn[]  = "internet";
TinyGsm modem(SerialAT);
TinyGsmClient clientGSM(modem);

CloudIoTCoreDevice device(project_id, location, registry_id, device_id,private_key_str);
CloudIoTCoreMQTTClient client(device);

void callback(uint8_t *payload, unsigned int length) {
  Serial.print("callback");
}

void setup() {
  // Set console baud rate
  Serial.begin(9600);
  delay(10);
  // Set GSM module baud rate
  SerialAT.begin(9600);
  delay(1000);
  Serial.println(F("Restarted"));
  wdt_init();
  wdt_reset();

  if (gsmRestart()) {
    if (gsmConnect()) {
      Serial.println("Connecting to mqtt.googleapis.com");
      client.connectSecure(root_cert);
      client.setConfigCallback(callback);
      String payload = "setup:";
      client.publishTelemetry(payload);
    }
  }
}

void loop() {
  String payload = "r:";
  client.publishTelemetry(payload);
}

bool gsmRestart() {
  Serial.print(F("Restarting modem: "));
  if (!modem.restart()) {
    Serial.println(F(" Modem fail"));
    wdt_reset();
    return false;
  }
  Serial.println(F("Modem restart OK"));
  // Unlock your SIM card with a PIN
  modem.simUnlock("1234");
  resetCounter = 0; //Sucessfull  = Reset the counter
  wdt_reset();
  return true;
}

bool gsmConnect() {
  Serial.print(F("Waiting for network: "));
  if (!modem.waitForNetwork()) {
    Serial.println(F(" Network failed, trying again"));
    wdt_reset();
    return false;
  }
  Serial.println(F("Network OK"));
  Serial.print(F("Connecting to "));
  Serial.print(apn);
  if (!modem.gprsConnect(apn, "", "")) {
    Serial.println(F("GPRS failed, trying again"));
    wdt_reset();
    return false;
  }
  delay(10);
  Serial.println(F(": GPRS OK"));
  resetCounter = 0; //Sucessfull  = Reset the counter
  wdt_reset();
  return true;
}
