# CAT 10 – STM32 and ESP8266 Wi-Fi Communication

## Overview
This folder contains experiments demonstrating communication between the STM32 Blue Pill and the ESP8266 Wi-Fi module using UART AT commands.

## Hardware and Software
- STM32 Blue Pill (STM32F103C8T6)
- ESP8266 / Wemos Wi-Fi module
- USB-to-TTL converter
- STM32CubeMX
- Keil MDK-ARM
- Arduino IDE (for module testing)
- STM32 HAL Library

## TASK A – UART Communication with ESP8266

**Objective:** Establish UART communication between STM32 and ESP8266.

**Implementation:**
- Configured UART communication.
- Sent AT commands from STM32 to ESP8266.
- Received responses from the ESP8266 module.

## TASK B – ESP8266 AT Commands

**Objective:** Explore and test the AT command interface of ESP8266.

**Implementation:**
- Tested basic AT commands.
- Checked module firmware information.
- Explored Wi-Fi configuration and network-related commands.

## TASK C – Wi-Fi Connection

**Objective:** Connect the ESP8266 module to a Wi-Fi network using AT commands.

**Implementation:**
- Configured the ESP8266 Wi-Fi mode.
- Used AT commands to connect to a Wi-Fi network.
- Checked the connection response.

## Tools Used
- STM32CubeMX
- Keil MDK-ARM
- Arduino IDE
- STM32 HAL Library

## Conclusion
The experiments demonstrated UART-based communication with the ESP8266, AT command execution, and Wi-Fi network connectivity.