# CAT 09 – STM32 UART Communication

## Overview
This folder contains experiments demonstrating UART communication between the STM32 Blue Pill and a computer, followed by command-based LED control.

## Hardware and Software
- STM32 Blue Pill (STM32F103C8T6)
- USB-to-TTL converter
- LED
- STM32CubeMX
- Keil MDK-ARM
- PuTTY
- STM32 HAL Library

## TASK A – UART Communication

**Objective:** Establish serial communication between the STM32 and a computer using UART.

**Implementation:**
- Configured UART communication.
- Transmitted messages from STM32 to the computer.
- Received data from the computer through UART.
- Implemented echo functionality to transmit received data back.

**Observation:** UART transmission and reception were demonstrated using a serial terminal.

## TASK B – String-Based LED Control

**Objective:** Control an LED using commands received through UART.

**Implementation:**
- Received command data through UART.
- Processed the received string.
- Controlled the LED based on the received command.

**Observation:** The LED responded to the commands received through the serial terminal.

## Tools Used
- STM32CubeMX
- Keil MDK-ARM
- PuTTY
- STM32 HAL Library

## Conclusion
The experiments demonstrated UART transmission, reception, echo communication, and command-based LED control using the STM32 Blue Pill.