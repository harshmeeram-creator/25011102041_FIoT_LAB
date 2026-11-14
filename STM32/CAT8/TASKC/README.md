# Task 8C – Short Press vs Long Press

## Experiment
STM32 GPIO Bring-Up and Switch-Controlled LED

## Problem Statement
Classify button presses based on duration and perform different LED operations.

## Press Duration
- Short press: Less than 1 second.
- Long press: 1 second or more.

## Expected Behaviour

| User Action | System Response |
|---|---|
| Short press | Toggle LED |
| Long press | LED enters continuous blinking mode |
| Next short press | Stop blinking |
| Long press again | Return to blinking mode |

## Important Constraint
Do not use a blocking delay to determine whether a button is held for a long press. Use a non-blocking time measurement approach.

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
1. Detect the button press and record the start time using `HAL_GetTick()`.
2. Continuously monitor the button state.
3. Calculate the press duration without blocking the program.
4. If the duration is less than 1 second, toggle the LED.
5. If the duration is 1 second or more, activate or deactivate blinking mode.
6. Continue monitoring button events.

## Core HAL Functions
- `HAL_GPIO_ReadPin()` – Read switch state.
- `HAL_GPIO_WritePin()` – Control LED.
- `HAL_GPIO_TogglePin()` – Toggle LED.
- `HAL_GetTick()` – Measure button press duration.
- `HAL_Delay()` – Optional.

## Circuit Diagram
The same push-button and LED circuit is used for Tasks 8A, 8B and 8C.

![STM32 GPIO Button and LED Circuit](../circuit.png)
