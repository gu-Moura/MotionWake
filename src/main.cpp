#include "config.h"
#include "OTA.h"
#include "WiFi.h"

 
void setup() {
  Serial.begin(115200);
  Serial.println("\n\nIniciando...");
  while (!connectWifi()) {
    Serial.println("Conexao falhou! Reiniciando...");
    delay(5000);
    ESP.restart();
  }   
 
  setUpOTA();

  Serial.println("Pronto");
  Serial.print("Endereco IP: ");
  Serial.println(getLocalIp());

  pinMode(D4, OUTPUT);
  pinMode(D3, INPUT);
}
 
void loop() {
  ArduinoOTA.handle();
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  Serial.print("Movimento: ");
  Serial.println(digitalRead(D3));
  delay(200);
}