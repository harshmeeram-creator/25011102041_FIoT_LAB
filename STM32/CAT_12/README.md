# EXPERIMENT DETAILS

**EXP:** CAT 12

**NAME OF EXP:** STM32 GPIO Experiments

**HARDWARE SETUP / PLATFORM:** NUCLEO-F410RB + STM32CubeMX + Keil MDK-ARM + STM32 HAL Library

---

## TASK NO

### Task A – On-board LED Bring-Up

**Objective:**

Configure and control the on-board LED.

**Implementation:**

1. Configure PA5 as GPIO output.
2. Initialize the GPIO peripheral.
3. Implement LED blinking using GPIO operations.

**Observation:**

The on-board LED blinked as expected.

### Task B – On-board Switch Control with State Remembrance

**Objective:**

Control the on-board LED using the user button and maintain its state.

**Implementation:**

1. Configure PC13 as GPIO input.
2. Configure PA5 as GPIO output.
3. Detect valid button presses.
4. Toggle the LED state whenever a valid button press is detected.
5. Maintain the LED's state until the next valid press.

**Observation:**

Each valid button press changed the LED state.

### Task C – Short-Press and Long-Press Detection

**Objective:**

Differentiate short and long button presses to control LED operations.

**Implementation:**

1. Implement button debouncing.
2. Use a 1-second threshold to distinguish short and long presses.
3. Use a short press to toggle the LED.
4. Use a long press to activate continuous LED blinking.
5. Use `HAL_GetTick()` for non-blocking timing.

**Observation:**

The LED responded differently to short and long button presses.

---

## CIRCUIT DIAGRAM

**Task A – On-board LED Bring-Up (LD2 – PA5)**

![On-board LED Circuit](circuit%20-%201.png)

**Tasks B and C – On-board LED and User Button (LD2 – PA5, B1 – PC13)**

![LED and User Button Circuit](circuit%20-%202.png)

---

## CORE LOGIC / PSEUDOCODE / CODE BASE

**Core Logic:**

- Configure PA5 as GPIO output for LED control.
- Configure PC13 as GPIO input for button detection.
- Use GPIO operations to control the LED.
- Implement button debouncing to avoid multiple detections.
- Use `HAL_GetTick()` to measure button press duration without blocking execution.
- Execute the required LED operation based on the detected button event.

**General Pseudocode:**

1. Initialize GPIO peripherals.
2. Configure PA5 as output.
3. For Task A, toggle the LED continuously.
4. For Task B:
   - Read the button state.
   - Detect a valid press.
   - Toggle and maintain the LED state.
5. For Task C:
   - Detect the button press.
   - Record the press start time.
   - Measure the press duration using `HAL_GetTick()`.
   - If less than 1 second, toggle the LED.
   - If 1 second or more, activate continuous blinking.
6. Repeat the required operations.

**Code Base:**

Separate task implementations are maintained in their respective task folders.

## INFERENCE

All three experiments demonstrate GPIO configuration and LED control using the NUCLEO-F410RB development board. The experiments cover on-board LED blinking, user-button-based state control, debouncing, and short-press/long-press detection using non-blocking timing with `HAL_GetTick()`.