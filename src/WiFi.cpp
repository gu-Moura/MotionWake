#include "config.h"

bool connectWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID_NAME, SSID_PASSWORD);
    return (WiFi.waitForConnectResult() != WL_CONNECTED) ? false : true;
}

IPAddress getLocalIp(){
    return WiFi.localIP();
}