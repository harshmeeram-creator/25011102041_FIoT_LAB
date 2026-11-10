@"
# CAT 08 – STM32 GPIO Bring-Up and Switch-Controlled LED

**Week:** 8  
**Date:** 18/09/2026  
**Platform:** STM32 Blue Pill  
**Tools:** STM32CubeMX, Keil MDK, STM32 HAL Libraries

## Objective
To understand STM32 GPIO configuration and implement switch-controlled LED operations using GPIO input and output.

## Tasks

### TASK 8A – GPIO Input/Output
- Interface a push-button and LED with STM32.
- Configure GPIO pins for input and output.
- Turn the LED ON when the switch is pressed.
- Turn the LED OFF when the switch is released.

### TASK 8B – Event-Based Control
- Modify the firmware so each valid switch press toggles the LED state.
- Investigate switch bounce.
- Implement software debouncing so one press produces one toggle.

### TASK 8C – Short Press vs Long Press
Classify button presses based on duration.

- **Short press:** Less than 1 second.
- **Long press:** 1 second or more.

| User Action | System Response |
|---|---|
| Short press | Toggle LED |
| Long press | LED enters continuous blinking mode |
| Next short press | Stop blinking |
| Long press again | Return to blinking mode |

**Important Constraint:** Do not use a blocking delay to determine whether a button is held for a long press. Use a non-blocking time measurement approach.

## Hardware Setup
- STM32 Blue Pill development board
- Push-button
- LED
- Current-limiting resistor
- Breadboard and jumper wires

## Core HAL Functions
- `HAL_GPIO_ReadPin()` – Read switch state.
- `HAL_GPIO_WritePin()` – Control LED.
- `HAL_GPIO_TogglePin()` – Toggle LED.
- `HAL_GetTick()` – Measure button press duration.
- `HAL_Delay()` – Optional for simple initial testing.

## Circuit Diagram
_To be added using the actual circuit diagrams._

## Implementation
Separate task implementations are maintained in their respective task folders.

## Observations
_To be completed using actual experiment observations._

## Result
STM32 GPIO input/output, event-based LED toggling, and short-press/long-press detection were implemented as specified.
"@ | Set-Content STM32\CAT_08\README.md -Encoding UTF8