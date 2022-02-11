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

// #include <FastLED.h>
#include <Adafruit_NeoPixel.h>

// RGB LED PIN D3 - D7
#define RGB_LED_PIN 4
#define NUMPIXELS 4
// CRGB leds[NUMPIXELS];
Adafruit_NeoPixel pixels(NUMPIXELS, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

// D2 , RGB LED 初期化
void setStatusLED(bool isON) {
  digitalWrite(D2, (isON)? HIGH : LOW);
  Serial.print("D2 "); Serial.println((isON)? "HIGH" : "LOW");  
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
  Serial.begin(115200);

  // D2
  pinMode(D2, OUTPUT);
  // IO4 RGB LED 初期化
  pinMode(RGB_LED_PIN, OUTPUT);
  // FastLED.addLeds<WS2812B, RGB_LED_PIN>(leds, NUMPIXELS);
  pixels.begin();

  // mDNS 設定
  wifiUtil.setupMDNS(MDNS_HOST, HTTP_PORT, 0);
  
  // WiFi 接続設定
  wifiUtil.setupWiFi(WIFI_SSID);
  Serial.print("WiFi connected, IP = "); Serial.println(WiFi.localIP());

  webServerSetup();
}

void loop() {
  /* 
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Red;
  leds[2] = CRGB::Red;
  leds[3] = CRGB::Red;
  FastLED.show();
  */
  pixels.setPixelColor(0, pixels.Color(128, 0, 0));
  pixels.setPixelColor(1, pixels.Color(128, 0, 0));
  pixels.setPixelColor(2, pixels.Color(128, 0, 0));
  pixels.setPixelColor(3, pixels.Color(128, 0, 0));
  pixels.show();

  setStatusLED(true);
  delay(500);

  /*
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  leds[2] = CRGB::Black;
  leds[3] = CRGB::Black;
  FastLED.show();
  */
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(3, pixels.Color(0, 0, 0));
  pixels.show();
  pixels.clear();

  setStatusLED(false);
  delay(500);
}