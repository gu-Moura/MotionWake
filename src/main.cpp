#include "config.h"
#include "OTA.h"
#include "WiFi.h"

#include <NTPClient.h>

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

AsyncWebServer server(80);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void recvMsg(uint8_t *data, size_t len)
{
  String d = "";
  for (int i = 0; i < len; i++)
  {
    d += char(data[i]);
  }
  WebSerial.println(d);
  if (d == "sleep")
  {
    WebSerial.println("Going to sleep now!!");
    ESP.deepSleep(30e6);
    delay(10);
  }
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);

  Serial.begin(115200);
  Serial.println("Conectando...");
  while (!connectWifi())
  {
    Serial.println("Conexao falhou! Reiniciando...");
    delay(5000);
    ESP.restart();
  }

  Serial.println("Pronto");
  Serial.print("Endereco IP: ");
  Serial.println(getLocalIp());
  setUpOTA();

  WebSerial.begin(&server);
  WebSerial.msgCallback(recvMsg);
  server.begin();

  timeClient.begin();
  timeClient.setTimeOffset(-10800); // Offset is given in seconds, so GMT -3 is actually GMT -10800
}

void loop()
{
  ArduinoOTA.handle();

  timeClient.update();

  digitalWrite(LED_BUILTIN, !digitalRead(PIR_PIN));

  String debug_msg = "Movimento: " + String(digitalRead(PIR_PIN)) + " | Horario: " + String(timeClient.getHours()) + ":" + String(timeClient.getMinutes()) + ":" + String(timeClient.getSeconds());
  // WebSerial.println(debug_msg);
  Serial.println(debug_msg);
  delay(250);
}
