# Task B – String-Based LED Control

## Experiment
STM32 UART Communication

## Hardware / Platform
- STM32 Blue Pill (STM32F103C8T6)
- USB-to-TTL Converter
- LED
- STM32CubeMX
- Keil MDK-ARM
- PuTTY
- STM32 HAL Library

## Objective
Control an LED using commands received through UART.

## Implementation
1. Receive command data through UART.
2. Process the received string.
3. Identify the received command.
4. Control the LED connected to PC13 based on the received command.

## Observation
The LED responded to the commands received through the serial terminal.

## Core Logic
- Configure and initialize UART communication.
- Receive strings through UART.
- Compare the received command.
- Control the PC13 LED according to the command.

## Circuit Diagram
![UART and LED Circuit Diagram](../../circuit - 2.png)
