#include "device_1_config.h"

// Software serial
#include <SoftwareSerial.h>
SoftwareSerial SerialAT(13, 12); // RX, TX

// GSM configuration
#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>

const char apn[]  = "internet";
TinyGsm modem(SerialAT);
TinyGsmClient clientGSM(modem);

PubSubClient client("mqtt.googleapis.com", 8883, callback, clientGSM);

/**
 * Calculates issued at / expiration times for JWT and places the time, as a
 * Unix timestamp, in the strings passed to the function. The time_size
 * parameter specifies the length of the string allocated for both iat and exp.
 */
static void GetIatExp(char* iat, char* exp, int time_size) {
  // TODO: Use time.google.com for iat
  time_t now_seconds = time(NULL);
  snprintf(iat, time_size, "%lu", now_seconds);
  snprintf(exp, time_size, "%lu", now_seconds + 3600);
  if (TRACE) {
    printf("IAT: %s\n", iat);
    printf("EXP: %s\n", exp);
  }
}

/**
 * Calculates a JSON Web Token (JWT) given the path to a EC private key and
 * Google Cloud project ID. Returns the JWT as a string that the caller must
 * free.
 */
static char* CreateJwt(const char* ec_private_path, const char* project_id) {
  char iat_time[sizeof(time_t) * 3 + 2];
  char exp_time[sizeof(time_t) * 3 + 2];
  uint8_t* key = NULL; // Stores the Base64 encoded certificate
  size_t key_len = 0;
  jwt_t *jwt = NULL;
  int ret = 0;
  char *out = NULL;

  // Read private key from file
  FILE *fp = fopen(ec_private_path, "r");
  if (fp == (void*) NULL) {
    printf("Could not open file: %s\n", ec_private_path);
    return "";
  }
  fseek(fp, 0L, SEEK_END);
  key_len = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  key = malloc(sizeof(uint8_t) * (key_len + 1)); // certificate length + \0

  fread(key, 1, key_len, fp);
  key[key_len] = '\0';
  fclose(fp);

  // Get JWT parts
  GetIatExp(iat_time, exp_time, sizeof(iat_time));

  jwt_new(&jwt);

  // Write JWT
  ret = jwt_add_grant(jwt, "iat", iat_time);
  if (ret) {
    printf("Error setting issue timestamp: %d", ret);
  }
  ret = jwt_add_grant(jwt, "exp", exp_time);
  if (ret) {
    printf("Error setting expiration: %d", ret);
  }
  ret = jwt_add_grant(jwt, "aud", project_id);
  if (ret) {
    printf("Error adding audience: %d", ret);
  }
  ret = jwt_set_alg(jwt, JWT_ALG_ES256, key, key_len);
  if (ret) {
    printf("Error during set alg: %d", ret);
  }
  out = jwt_encode_str(jwt);

  // Print JWT
  if (TRACE) {
    printf("JWT: [%s]", out);
  }

  jwt_free(jwt);
  free(key);
  return out;
}

const char* password = char* CreateJwt(private_key_str, project_id); 

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
      client.connect(projects/{project-id}/locations/{location}/registries/{registry-id}/devices/{device-id}, null, password)
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
