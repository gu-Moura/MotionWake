#include <stdint.h>
#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char OTA_HOSTNAME[] = "MotionWake";
const char OTA_PASSWD[] = "123456";
const uint16_t OTA_PORT = 8266;

#define PIR_PIN D3