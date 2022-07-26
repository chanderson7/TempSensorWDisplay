#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN D7     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0X3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
  display.display();
}

void loop() {
    Serial.print("Temperature = ");
    float temp = dht.readTemperature();
    float degreesFar = (temp * 1.8) + 32;
    Serial.println(degreesFar);
    Serial.print("Humidity = ");
    Serial.println(dht.readHumidity());
    displayTempAndHum(degreesFar, dht.readHumidity());
    delay(10000);
}

void displayTempAndHum(float temp, float hum) {
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);
  display.println("Temperature");
  display.println("-------------------");
  display.print("     ");
  display.setTextSize(2);
  display.print(temp, 1);
  display.println((char)247);
  display.setTextSize(1);
  display.println("Humidity");
  display.println("-------------------");
  display.print("     ");
  display.setTextSize(2);
  display.print(hum, 1);
  display.print("%");
  display.display();
}
