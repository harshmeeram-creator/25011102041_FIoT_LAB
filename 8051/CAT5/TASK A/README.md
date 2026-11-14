# CAT5 – Task A: Hardware Timer and Interrupt-Based LED Control

## EXPERIMENT DETAILS
- Experiment: Continuous Lab Evaluation – 5
- Date: 10/08/2026 (Week 4)
- Microcontroller: AT89S52 (8051)
- Crystal Frequency: 11.0592 MHz
- Programming Language: Embedded C
- IDE: Keil µVision – Keil C51
- Timer: Timer 0, Mode 1 (16-bit)

## OBJECTIVE
Configure Timer 0 in 16-bit Mode 1 and use periodic interrupts to toggle an LED at one-second intervals.

## CORE LOGIC
1. Configure Timer 0 in Mode 1.
2. Load the timer's initial value.
3. Enable Timer 0 interrupts.
4. Reload the timer inside the interrupt service routine.
5. Maintain a software counter.
6. Toggle the LED after the required interval.

## TIMER CALCULATION
- Machine cycle time ≈ 1.085 µs
- Counts for approximately 1 ms ≈ 922
- Preload = 65536 - 922 = 64614 = FC66H

```c
TH0 = 0xFC;
TL0 = 0x66;
CODE BASE
- cat5_task1_timer0_led_toggle.c
CIRCUIT DIAGRAM
INFERENCE
Timer 0 interrupts provide periodic timing for LED control and demonstrate timer configuration and interrupt handling using Embedded C.
