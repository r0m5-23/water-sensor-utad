#include <MKRWAN.h>
#include "arduino_secrets.h"

String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;

// Select your region (AS923, AU915, EU868, KR920, IN865, US915, US915_HYBRID)
_lora_band region = EU868;

LoRaModem modem(Serial1);

uint16_t voltage = 0;
uint8_t txBuffer[2];


void setup() {

  Serial.begin(115200);
  pinMode(A0, INPUT);

  while (!Serial);
  if (!modem.begin(region)) {
    Serial.println("Failed to start module");
    while (1) {}
  };

  // Apagar ???
  /*
    Serial.print("Your module version is: ");
    Serial.println(modem.version());
    Serial.print("Your device EUI is: ");
    Serial.println(modem.deviceEUI());
  */

  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }


  modem.minPollInterval(60);
  // NOTA: modem só permite enviar msg a cada 2 min
}

void loop() {

  voltage = (uint16_t)(analogRead(A0) * 5.0 / 1023.0 * 100);
  txBuffer[0] = (voltage >> 8) & 0xff;
  txBuffer[1]  = voltage & 0xff;

  // Apagar ou comentar quando pronto
  Serial.println(txBuffer[0], HEX);
  Serial.println(txBuffer[1], HEX);
  //float rec = (float)(((txBuffer[0] << 8) | txBuffer[1])/100.0);
  //Serial.println(rec);


  int err;
  modem.beginPacket();
  modem.write(txBuffer);
  
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }
}
