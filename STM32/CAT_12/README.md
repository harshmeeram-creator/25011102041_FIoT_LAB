# CAT 12 – STM32 GPIO Experiments

## Overview
This folder contains three experiments demonstrating LED control and push-button operations using the NUCLEO-F410RB development board.

## Hardware and Software
- NUCLEO-F410RB
- On-board LED (LD2 – PA5)
- On-board User Button (B1 – PC13)
- STM32CubeMX
- Keil MDK-ARM
- STM32 HAL Library

## TASK A – On-board LED Bring-Up

**Objective:** Configure and control the on-board LED.

**Implementation:**
- Configured PA5 as GPIO output.
- Implemented LED blinking using GPIO operations.

**Observation:** The on-board LED blinked as expected.

## TASK B – On-board Switch Control with State Remembrance

**Objective:** Control the on-board LED using the user button and maintain its state.

**Implementation:**
- Configured PC13 as GPIO input.
- Configured PA5 as GPIO output.
- Used button presses to toggle the LED state.

**Observation:** Each valid button press changed the LED state.

## TASK C – Short-Press and Long-Press Detection

**Objective:** Differentiate short and long button presses to control LED operations.

**Implementation:**
- Implemented button debouncing.
- Used a 1-second threshold to distinguish short and long presses.
- Short press toggled the LED.
- Long press activated continuous LED blinking.
- Used HAL_GetTick() for non-blocking timing.

**Observation:** The LED responded differently to short and long button presses.

## Tools Used
- STM32CubeMX
- Keil MDK-ARM
- STM32 HAL Library

## Conclusion
All three experiments demonstrated GPIO configuration, LED control, button handling, debouncing, and press-duration detection using the NUCLEO-F410RB board.