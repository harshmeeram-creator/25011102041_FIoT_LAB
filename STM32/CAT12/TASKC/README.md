# Task C – Short-Press and Long-Press Detection

## Experiment
STM32 GPIO Experiments

## Hardware / Platform
- NUCLEO-F410RB
- STM32CubeMX
- Keil MDK-ARM
- STM32 HAL Library

## Objective
Differentiate short and long button presses to control LED operations.

## Implementation
1. Implement button debouncing.
2. Use a 1-second threshold to distinguish short and long presses.
3. Use a short press to toggle the LED.
4. Use a long press to activate continuous LED blinking.
5. Use `HAL_GetTick()` for non-blocking timing.

## Observation
The LED responded differently to short and long button presses.

## Core Logic
- Configure GPIO for LED and button control.
- Implement button debouncing.
- Record the button press start time.
- Measure press duration using `HAL_GetTick()`.
- If less than 1 second, toggle the LED.
- If 1 second or more, activate continuous blinking.

## Circuit Diagram
![LED and User Button Circuit](../../circuit - 2.png)
