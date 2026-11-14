# Task A – UART Communication

## Experiment
STM32 UART Communication

## Hardware / Platform
- STM32 Blue Pill (STM32F103C8T6)
- USB-to-TTL Converter
- STM32CubeMX
- Keil MDK-ARM
- PuTTY
- STM32 HAL Library

## Objective
Establish serial communication between the STM32 and a computer using UART.

## Implementation
1. Configure UART communication using STM32CubeMX.
2. Initialize UART using STM32 HAL functions.
3. Transmit messages from the STM32 to the computer.
4. Receive data from the computer through UART.
5. Implement echo functionality to transmit received data back.

## Observation
UART transmission and reception were demonstrated successfully using a serial terminal.

## Core Logic
- Configure and initialize UART communication.
- Transmit messages from STM32 to the computer.
- Receive characters or strings through UART.
- Echo the received data back to the terminal.

## Circuit Diagram
![UART Circuit Diagram](../../circuit - 1.png)
