/*
 * WingGlobe by zsharpminor :3
 * This code is NOT final and will be adjusted once parts in hand!!
 * Only uses the inbuilt sensor for now as I'm tired, I'll add the switching mechanic later.
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "ClosedCube_HDC1080.h"
#include <GxEPD2_3C.h>
#include <SPI.h>

const char* WIFI_SSID     = "redacted_for_privacy";
const char* WIFI_PASS     = "what_ru_looking_for_weatherboy";
String OWM_API_KEY        = "i_said_redacted";
String CITY               = "Mill Valley";
String COUNTRY            = "US";

#define PIN_FAN_MOSFET    2
#define PIN_LEDS          1
#define NUM_LEDS          16
#define PIN_I2C_SDA       5
#define PIN_I2C_SCL       6

#define EINK_CS           3
#define EINK_DC           4
#define EINK_RST          43
#define EINK_BUSY         44
#define EINK_SCK          7
#define EINK_MOSI         9

GxEPD2_3C<GxEPD2_290_Z13c, GxEPD2_290_Z13c::HEIGHT> display(GxEPD2_290_Z13c(EINK_CS, EINK_DC, EINK_RST, EINK_BUSY));

Adafruit_NeoPixel strip(NUM_LEDS, PIN_LEDS, NEO_GRB + NEO_KHZ800);
ClosedCube_HDC1080 hdc1080;

unsigned long lastTime = 0;
unsigned long timerDelay = 600000;

void setup() {
  Serial.begin(115200);

  pinMode(PIN_FAN_MOSFET, OUTPUT);
  ledcAttach(PIN_FAN_MOSFET, 25000, 8);

  strip.begin();
  strip.show();

  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  hdc1080.begin(0x40);

  SPI.begin(EINK_SCK, -1, EINK_MOSI, EINK_CS);
  display.init(0);
  display.setRotation(3);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  updateWeather();
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    updateWeather();
    lastTime = millis();
  }
}

void updateWeather() {
  if(WiFi.status() != WL_CONNECTED) return;

  String url = "http://api.openweathermap.org/data/2.5/weather?q=" + CITY + "," + COUNTRY + "&APPID=" + OWM_API_KEY + "&units=metric";
  
  WiFiClient client;
  HTTPClient http;
  http.begin(client, url);
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    String payload = http.getString();
    JSONVar data = JSON.parse(payload);

    if (JSON.typeof(data) != "undefined") {
      double temp = (double)data["main"]["temp"];
      int humidity = (int)data["main"]["humidity"];
      double wind = (double)data["wind"]["speed"];
      int id = (int)data["weather"][0]["id"];
      String desc = (const char*)data["weather"][0]["description"];

      double localTemp = hdc1080.readTemperature();
      double localHum = hdc1080.readHumidity();

      setFan(wind);
      setLeds(id);
      drawDisplay(temp, humidity, wind, desc, localTemp, localHum);
    }
  }
  http.end();
}

void setFan(double speed) {
  int pwm = map((long)speed, 0, 15, 0, 255);
  pwm = constrain(pwm, 0, 255);
  ledcWrite(PIN_FAN_MOSFET, pwm);
}

void setLeds(int id) {
  uint32_t c1, c2;

  if (id >= 200 && id < 300) { 
    c1 = strip.Color(150, 150, 150); c2 = strip.Color(0, 0, 100);
  } else if (id >= 300 && id < 600) { 
    c1 = strip.Color(0, 0, 255); c2 = strip.Color(0, 0, 50);
  } else if (id >= 800 && id < 802) { 
    c1 = strip.Color(255, 255, 0); c2 = strip.Color(255, 100, 0);
  } else if (id >= 802) { 
    c1 = strip.Color(200, 200, 200); c2 = strip.Color(100, 100, 255);
  } else {
    c1 = strip.Color(50, 50, 50); c2 = strip.Color(0, 0, 0);
  }

  for(int i=0; i<NUM_LEDS; i++) {
    float r = (float)i / (NUM_LEDS - 1);
    uint8_t red = (uint8_t)(( (c1 >> 16) * (1-r)) + ((c2 >> 16) * r));
    uint8_t grn = (uint8_t)(( ((c1 >> 8) & 0xFF) * (1-r)) + ((c2 >> 8 & 0xFF) * r));
    uint8_t blu = (uint8_t)(( (c1 & 0xFF) * (1-r)) + ((c2 & 0xFF) * r));
    strip.setPixelColor(i, strip.Color(red, grn, blu));
  }
  strip.show();
}

void drawDisplay(double t, int h, double w, String d, double lt, double lh) {
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    
    display.setTextColor(GxEPD_BLACK);
    display.setTextSize(1);
    display.setCursor(0, 10);
    display.println("WEATHER STATION");
    
    display.setTextSize(2);
    display.setCursor(0, 30);
    display.print(t, 1); display.print("C "); display.print(h); display.println("%");
    
    display.setTextColor(GxEPD_RED);
    display.setTextSize(1);
    display.setCursor(0, 55);
    display.print("Wind: "); display.print(w); display.println(" m/s");
    display.println(d);

    display.setTextColor(GxEPD_BLACK);
    display.drawLine(0, 80, display.width(), 80, GxEPD_BLACK);

    display.setCursor(0, 90);
    display.println("INDOOR:");
    display.setTextSize(2);
    display.setCursor(0, 105);
    display.print(lt, 1); display.print("C "); display.print(lh, 0); display.println("%");

  } while (display.nextPage());
}
