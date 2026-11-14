# Task 8B – Event-Based Control

## Experiment
STM32 GPIO Bring-Up and Switch-Controlled LED

## Problem Statement
Modify the firmware so each valid switch press toggles the LED state. Investigate switch bounce and implement software debouncing so one press produces one toggle.

## Hardware / Platform
- STM32 Blue Pill
- STM32CubeMX
- Keil MDK
- STM32 HAL Libraries
- Push-button
- LED
- Current-limiting resistor
- Breadboard and jumper wires

## Core Logic
1. Read the push-button state.
2. Detect a valid button press.
3. Apply software debouncing.
4. Toggle the LED only once for each valid press.
5. Wait for the button release before detecting the next press.

## Core HAL Functions
- `HAL_GPIO_ReadPin()` – Read switch state.
- `HAL_GPIO_TogglePin()` – Toggle LED.

## Circuit Diagram
The same push-button and LED circuit is used for Tasks 8A, 8B and 8C.

![STM32 GPIO Button and LED Circuit](../circuit.png)
