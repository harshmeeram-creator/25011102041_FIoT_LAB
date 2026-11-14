# Task C – Wi-Fi Connection

## Experiment
STM32 and ESP8266 Wi-Fi Communication

## Hardware / Platform
- STM32 Blue Pill (STM32F103C8T6)
- ESP8266 / Wemos Wi-Fi Module
- USB-to-TTL Converter
- STM32CubeMX
- Keil MDK-ARM
- STM32 HAL Library

## Objective
Connect the ESP8266 module to a Wi-Fi network using AT commands.

## Implementation
1. Configure the ESP8266 Wi-Fi mode.
2. Send AT commands to connect to a Wi-Fi network.
3. Receive and check the connection response.
4. Verify successful network connectivity.

## Core Logic
- Initialize UART communication with ESP8266.
- Configure the Wi-Fi operating mode.
- Send the required AT commands.
- Connect the ESP8266 to the Wi-Fi network.
- Receive and verify the connection response.

## Circuit Diagram
![STM32 ESP8266 Circuit Diagram](../../circuit.png)
