# Task B – On-board Switch Control with State Remembrance

## Experiment
STM32 GPIO Experiments

## Hardware / Platform
- NUCLEO-F410RB
- STM32CubeMX
- Keil MDK-ARM
- STM32 HAL Library

## Objective
Control the on-board LED using the user button and maintain its state.

## Implementation
1. Configure PC13 as GPIO input.
2. Configure PA5 as GPIO output.
3. Detect valid button presses.
4. Toggle the LED state whenever a valid button press is detected.
5. Maintain the LED's state until the next valid press.

## Observation
Each valid button press changed the LED state.

## Core Logic
- Configure PC13 as GPIO input and PA5 as GPIO output.
- Read the button state.
- Detect a valid button press.
- Toggle and maintain the LED state.

## Circuit Diagram
![LED and User Button Circuit](../../circuit - 2.png)
