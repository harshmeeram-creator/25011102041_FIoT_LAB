# Task 8A – GPIO Input/Output

## Experiment
STM32 GPIO Bring-Up and Switch-Controlled LED

## Problem Statement
Interface a push-button and LED with the STM32. Configure GPIO pins for input and output. Turn the LED ON when the switch is pressed and turn it OFF when the switch is released.

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
1. Configure the required GPIO pins for input and output.
2. Read the push-button state using `HAL_GPIO_ReadPin()`.
3. Turn the LED ON when the switch is pressed.
4. Turn the LED OFF when the switch is released.
5. Repeat continuously.

## Core HAL Functions
- `HAL_GPIO_ReadPin()` – Read switch state.
- `HAL_GPIO_WritePin()` – Control LED.

## Circuit Diagram
The same push-button and LED circuit is used for Tasks 8A, 8B and 8C.

![STM32 GPIO Button and LED Circuit](../circuit.png)
