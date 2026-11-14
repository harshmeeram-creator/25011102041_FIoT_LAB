# EXPERIMENT DETAILS

**EXP:** Continuous Lab Evaluation – 9

**NAME OF EXP:** STM32 UART Communication

**HARDWARE SETUP / PLATFORM:** STM32 Blue Pill (STM32F103C8T6) + USB-to-TTL Converter + LED + STM32CubeMX + Keil MDK-ARM + PuTTY + STM32 HAL Library

---

## TASK NO

### Task A – UART Communication

**Objective:**

Establish serial communication between the STM32 and a computer using UART.

**Implementation:**

1. Configure UART communication using STM32CubeMX.
2. Initialize UART using STM32 HAL functions.
3. Transmit messages from the STM32 to the computer.
4. Receive data from the computer through UART.
5. Implement echo functionality to transmit received data back.

**Observation:**

UART transmission and reception were demonstrated successfully using a serial terminal.

### Task B – String-Based LED Control

**Objective:**

Control an LED using commands received through UART.

**Implementation:**

1. Receive command data through UART.
2. Process the received string.
3. Identify the received command.
4. Control the LED connected to PC13 based on the received command.

**Observation:**

The LED responded to the commands received through the serial terminal.

---

## CIRCUIT DIAGRAM

**Task A – UART Communication**

![UART Circuit Diagram](circuit%20-%201.png)

**Task B – UART-Based LED Control**

![UART and LED Circuit Diagram](circuit%20-%202.png)

---

## CORE LOGIC / PSEUDOCODE / CODE BASE

**Core Logic:**

- Configure and initialize UART communication.
- Transmit messages from STM32 to the computer.
- Receive characters or strings through UART.
- For Task A, echo the received data back to the terminal.
- For Task B, process the received command and control the PC13 LED.

**General Pseudocode:**

1. Initialize GPIO and UART peripherals.
2. Start UART communication.
3. Transmit the required message.
4. Receive data from the serial terminal.
5. For Task A, transmit the received data back.
6. For Task B, compare the received command.
7. Control the LED according to the command.
8. Repeat the communication process.

**Code Base:**

Separate task implementations are maintained in their respective task folders.

## INFERENCE

The experiment demonstrates UART transmission, reception, and echo communication using the STM32 Blue Pill. UART-based string commands are also used to control an LED connected to PC13. The experiment provides practical understanding of serial communication, UART configuration, and command-based GPIO control using STM32 HAL libraries.