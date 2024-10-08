#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LoRa.h>
#include <Fonts/FreeSans9pt7b.h>
#include "BluetoothSerial.h"

#define NODE_ID 1 // Assign a unique ID for each node

// This is the LoRa(tm) image
#define logo_width 99
#define logo_height 64

const uint8_t logo_bits[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xD7, 0x06, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x29, 
  0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 
  0x00, 0xB4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0x0B, 0x00, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xA8, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xA0, 0x77, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x7A, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xD8, 0x00, 0x00, 0x00, 0x00, 0xB8, 0x6D, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0xFC, 0x01, 0xFC, 
  0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0xC0, 0x01, 0x06, 
  0xFC, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 
  0x08, 0xFC, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 
  0x00, 0x00, 0xF8, 0xBB, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 
  0x00, 0x00, 0x00, 0xFC, 0x00, 0x7F, 0x00, 0x00, 0x04, 0x00, 0x00, 0xFC, 
  0x00, 0x00, 0xFE, 0x00, 0xFC, 0x00, 0x7E, 0xC0, 0x3F, 0x90, 0x00, 0x00, 
  0xFC, 0x00, 0x80, 0xFF, 0x07, 0xFC, 0x00, 0x7E, 0xF0, 0xFF, 0x44, 0x00, 
  0x00, 0xFC, 0x00, 0xC0, 0xFF, 0x0F, 0xFC, 0x00, 0x7E, 0xF8, 0xFF, 0x21, 
  0x00, 0x00, 0xFC, 0x00, 0xE0, 0xFF, 0x1F, 0xFC, 0x00, 0x7E, 0xF8, 0xF1, 
  0x03, 0x00, 0x00, 0xFC, 0x00, 0xE0, 0x87, 0x1F, 0xFC, 0x00, 0x7F, 0x7C, 
  0xF0, 0x01, 0x00, 0x00, 0xFC, 0x00, 0xF0, 0x03, 0x3F, 0xFC, 0xBB, 0x3F, 
  0x68, 0xE0, 0x03, 0x00, 0x00, 0xFC, 0x00, 0xF0, 0x01, 0x3E, 0xFC, 0xFF, 
  0x1F, 0x00, 0xE0, 0x03, 0x00, 0x00, 0xFC, 0x00, 0xF0, 0x01, 0x3E, 0xFC, 
  0xFF, 0x1F, 0x80, 0xFF, 0x01, 0x00, 0x00, 0xFC, 0x00, 0xF8, 0x01, 0x7C, 
  0xFC, 0xFF, 0x07, 0xE0, 0xFF, 0x03, 0x00, 0x00, 0xFC, 0x00, 0xF0, 0x01, 
  0x3E, 0xFC, 0xFF, 0x03, 0xF8, 0xFF, 0x03, 0x00, 0x00, 0xFC, 0x00, 0xF8, 
  0x00, 0x3E, 0xFC, 0xE0, 0x07, 0xFC, 0xE1, 0x03, 0x00, 0x00, 0xFC, 0x00, 
  0xF0, 0x01, 0x7E, 0xFC, 0xE0, 0x0F, 0xFC, 0xF0, 0x03, 0x00, 0x00, 0xFC, 
  0x00, 0xF0, 0x01, 0x3E, 0xFC, 0xE1, 0x0F, 0x7E, 0xF0, 0x01, 0x00, 0x00, 
  0xFC, 0x96, 0xF1, 0x03, 0x3F, 0xFC, 0xC0, 0x1F, 0x3C, 0xF0, 0x03, 0x00, 
  0x00, 0xFC, 0xFF, 0xE3, 0x87, 0x1F, 0xF8, 0x80, 0x1F, 0x7C, 0xF8, 0x03, 
  0x00, 0x00, 0xFC, 0xFF, 0xE1, 0xFF, 0x1F, 0xFC, 0x80, 0x3F, 0xFC, 0xFF, 
  0x01, 0x00, 0x00, 0xFC, 0xFF, 0xC3, 0xFF, 0x0F, 0xFC, 0x00, 0x7F, 0xFC, 
  0xFF, 0x03, 0x00, 0x00, 0xFC, 0xFF, 0x81, 0xFF, 0x07, 0xFC, 0x00, 0x7F, 
  0xF8, 0xEF, 0x03, 0x00, 0x00, 0xA8, 0x29, 0x00, 0xFE, 0x00, 0x54, 0x00, 
  0x12, 0xE0, 0x43, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xFC, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x08, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x18, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x95, 0x0D, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x01, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x02, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x80, 0x06, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA4, 0x00, 0xA0, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x5D, 
  0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0xB5, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00,
};

#define LORA_BAND    915

#define OLED_SDA    4
#define OLED_SCL    15
#define OLED_RST    16

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RST);

BluetoothSerial SerialBT;

// Forward declarations
void displayLoraData(String countStr);
void showLogo();

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println("LoRa Transmitter");

  SerialBT.begin("LoRaTransmitter"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");



  // Configure OLED by setting the OLED Reset HIGH, LOW, and then back HIGH
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, HIGH);
  delay(100);
  digitalWrite(OLED_RST, LOW);
  delay(100);
  digitalWrite(OLED_RST, HIGH);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  showLogo();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.print(F("LoRa Transmitter"));
  display.display();
  delay(2000);

  // Configure the LoRa radio
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(LORA_BAND * 1E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  // Set spreading factor to 12 (max range, min data rate)
  LoRa.setSpreadingFactor(12);
  // Set signal bandwidth to 125 kHz (lower bandwidth increases range)
  LoRa.setSignalBandwidth(125E3);
  // Set coding rate to 4/8 (higher coding rate increases robustness and range)
  LoRa.setCodingRate4(8);
  // Set the transmission power (max power is usually 20 dBm)
  LoRa.setTxPower(20);

  Serial.println("init ok");
}

void loop() {
  static int counter = 0;

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  String countStr = String(counter, DEC);
  Serial.println(countStr);
  displayLoraData(countStr);
  counter++;
  delay(1500);
}

void displayLoraData(String countStr) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print(F("Node ID 1"));
  display.print(F("Sending packet: "));
  display.print(countStr);
  display.display();
}

void showLogo() {
  uint8_t x_off = (display.width() - logo_width) / 2;
  uint8_t y_off = (display.height() - logo_height) / 2;

  display.clearDisplay();
  display.drawBitmap(x_off, y_off, logo_bits, logo_width, logo_height, SSD1306_WHITE);
  display.display();
}
