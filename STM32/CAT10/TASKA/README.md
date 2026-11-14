# Task A – UART Communication with ESP8266

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
Establish UART communication between STM32 and ESP8266.

## Implementation
1. Configure UART communication using STM32CubeMX.
2. Initialize UART using STM32 HAL functions.
3. Send AT commands from STM32 to ESP8266.
4. Receive and examine responses from the ESP8266 module.

## Core Logic
- Initialize UART communication between STM32 and ESP8266.
- Send AT commands through the UART interface.
- Receive and process responses from the ESP8266.

## Circuit Diagram
![STM32 ESP8266 Circuit Diagram](../../circuit.png)
