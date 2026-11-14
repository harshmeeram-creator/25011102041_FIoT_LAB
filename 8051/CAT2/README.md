# CAT 2 – 8051 Bare-Metal LED Blinking

## EXP
CAT 2 – Continuous Lab Evaluation 2

## DATE
20/07/2026 (Week 2)

## NAME OF EXP
8051 Tool Chain Setup and Bare-Metal LED Blinking Using AT89S52

## HARDWARE SETUP / PLATFORM
- Microcontroller: AT89S52
- Development Board: 8051 Development Board
- Programming Language: Embedded C
- Compiler: Keil C51
- Peripherals:
  - LED
  - Crystal Oscillator
  - Power Supply
  - Programmer / Debugger
- GPIO Configuration:
  - LED – P1.0 (verify actual board connection)

## TASK NO
**8051 Tool Chain Setup and Bare-Metal LED Blinking**

Compile a minimal bare-metal C program, program the AT89S52 microcontroller, and control an LED by directly accessing the microcontroller's memory-mapped GPIO registers.

### Required Activities

1. **Hardware Board Bring-Up:** Identify the microcontroller, programmer, power source, user LED and relevant GPIO pin.
2. **Power Verification:** Verify the board power rails using a digital multimeter.
3. **GPIO Configuration:** Configure the LED GPIO pin as an output using direct register access.
4. **Software Delay:** Implement a custom delay function using a software loop.
5. **LED Blinking:** Blink the LED at approximately 1 Hz.

## HARDWARE BRING-UP SHEET

| Parameter | Student Entry |
|---|---|
| MCU | AT89S52 |
| CPU Core | 8051 |
| Operating Voltage | 5V (verify board supply) |
| Debug Interface | Board programmer |
| LED GPIO Port | Port 1 (assumed) |
| LED GPIO Pin | P1.0 (verify board connection) |
| LED Active State | Active HIGH (verify board connection) |
| LED Frequency | Approximately 1 Hz |

## Circuit Diagram

![Circuit Diagram](circuit.png)

## Core Logic / Pseudocode / Code Base

### Core Logic
- Identify the AT89S52 microcontroller and development board.
- Configure the LED GPIO pin as an output.
- Access the GPIO pin directly using the 8051 register declaration.
- Create a custom delay function using nested software loops.
- Turn the LED ON and OFF with a delay between each state.
- Repeat the process continuously to produce LED blinking.

### Pseudocode
1. Start.
2. Initialize the LED GPIO pin.
3. Set the LED to OFF.
4. Turn the LED ON.
5. Call the custom delay function.
6. Turn the LED OFF.
7. Call the custom delay function.
8. Repeat continuously.

### Code Base
- `main.c`
- Keil project file (`.uvproj` or `.uvprojx`)
- `STARTUP.A51`, if generated/required by the project
- Compiled HEX file (`.hex`)

## Custom Delay Function
The `delay_ms()` function generates an approximate delay using nested software loops. It is used to control the LED ON and OFF timing.

## INFERENCE

The AT89S52 microcontroller demonstrates bare-metal programming through direct GPIO register access. A custom software delay function is used to generate an approximately 1 Hz LED blinking pattern without using Arduino APIs, HAL libraries or RTOS services.