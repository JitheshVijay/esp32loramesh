# LoRa Mesh Network with OLED Display and Bluetooth

This project demonstrates how to set up a LoRa mesh network using TTGO LoRa32 SX1276 OLED boards. Each node in the network can transmit and receive messages via LoRa, display data on an OLED screen, and connect to other devices using Bluetooth.

## Features

- LoRa Communication: Set up a robust LoRa mesh network for long-range communication.
- OLED Display: Display transmitted and received data on an OLED screen.
- Bluetooth Connectivity: Enable Bluetooth for additional device connectivity and debugging.

## Hardware Requirements

TTGO LoRa32 SX1276 OLED board

## Libraries Used

## Libraries Used

- `SPI.h`
- `Wire.h`
- `Adafruit_GFX.h`
- `Adafruit_SSD1306.h`
- `LoRa.h`
- `BluetoothSerial.h`

## Code Overview

The main code initializes the LoRa and Bluetooth modules, configures the OLED display, and provides functions to send and receive messages. The OLED screen displays the received data, while the Bluetooth module allows for debugging and additional connectivity.

