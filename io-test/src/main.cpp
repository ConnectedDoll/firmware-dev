#include <Arduino.h>

#include "WifiUtil.h"

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>

WifiUtil wifiUtil;
// AP モード SSID
const char* WIFI_SSID = "ConnectedDoll-DEV";
// mDNS ホスト名
const char* MDNS_HOST = "connecteddoll-dev";
// HTTP ポート
const int HTTP_PORT = 80;

AsyncWebServer webServer(HTTP_PORT);

// LED D2
#define D2 13

// D2 
void setStatusLED(bool isON) {
  digitalWrite(D2, (isON)? HIGH : LOW);
}

void webServerSetup() {
  Serial.println("webServerSetup");
  {
    // IPAddress 取得 API
    // curl -X POST -H "Content-Type: application/json" -d '{}' http://connecteddoll.local/api/ip    
    AsyncCallbackJsonWebHandler* handler = new AsyncCallbackJsonWebHandler("/api/ip", [](AsyncWebServerRequest *request, JsonVariant &json) {
      setStatusLED(true);
      IPAddress localIP = WiFi.localIP();
      String output = "{\"status\":\"OK\",\"ip\":\"" + localIP.toString() + "\"}";
      request->send(200, "application/json", output);

      setStatusLED(false);  
    });
    webServer.addHandler(handler);
  }

  webServer.begin();
}

void setup() {
  // mDNS 設定
  wifiUtil.setupMDNS(MDNS_HOST, HTTP_PORT, 0);
  
  // WiFi 接続設定
  wifiUtil.setupWiFi(WIFI_SSID);
  Serial.print("WiFi connected, IP = "); Serial.println(WiFi.localIP());

  webServerSetup();
}

void loop() {
  
}