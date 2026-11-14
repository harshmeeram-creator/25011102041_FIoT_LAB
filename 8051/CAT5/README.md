# CAT5 – Hardware Timer and Interrupt-Based Timing

## EXP
Continuous Lab Evaluation – 5

## DATE
10/08/2026 (Week 4)

## NAME OF EXP
Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control

## HARDWARE SETUP / PLATFORM
- **Microcontroller:** AT89S52 (8051)
- **Crystal Frequency:** 11.0592 MHz
- **Programming Language:** Embedded C
- **IDE / Compiler:** Keil µVision – Keil C51
- **Hardware:** AT89S52 Development Board, LEDs, Stepper Motor (optional), Motor Driver (if used), and Oscilloscope
- **Debugging Tool:** Multimeter
- **Timer:** Timer 0
- **Programming Method:** Register-level programming using hardware timer interrupts
- **Restrictions:** No Arduino APIs, HAL libraries, or RTOS services.

## TASK NO

### Task 1 – Timer 0 Interrupt and 1-Second LED Control

**Problem Statement:**

Configure Timer 0 to generate periodic interrupts. Use the timer interrupt as a software time base to toggle an LED every 1 second without using software delay loops for timing.

**Core Logic:**
1. Configure Timer 0 in Mode 1 (16-bit timer mode).
2. Load the timer registers with the required initial value.
3. Enable Timer 0 interrupt and global interrupt.
4. Reload the timer inside the interrupt service routine.
5. Maintain a software counter to track elapsed time.
6. Toggle the LED whenever the counter reaches 1 second.

**Timer Calculation:**

For a classic 12-clock 8051 with an 11.0592 MHz crystal:

- Machine cycle = 12 / 11.0592 MHz ≈ 1.085 µs
- Timer counts for 1 ms ≈ 922
- Timer preload = 65536 − 922 = 64614 = FC66H
- TH0 = 0xFC
- TL0 = 0x66

### Task 2 – LED Fading Using Software PWM

**Problem Statement:**

Use Timer 0 interrupts to generate a software PWM signal. Gradually vary the LED duty cycle from 0% to 100% and back to 0% to produce a visible fading effect.

**Core Logic:**
1. Generate periodic interrupts using Timer 0.
2. Divide each PWM period into multiple time slots.
3. Compare the PWM counter with the duty-cycle value.
4. Turn the LED ON or OFF based on the comparison.
5. Increase the duty cycle gradually from 0% to 100%.
6. Decrease the duty cycle gradually from 100% to 0%.
7. Repeat the fading sequence continuously.

**Duty-Cycle Sequence:**

0% → 10% → 20% → 30% → 40% → 50% → 60% → 70% → 80% → 90% → 100% → 90% → ... → 0%

**Suggested PWM Frequency:** 500 Hz – 1 kHz

### Task 3 – Variable-Frequency Square-Wave Generation

**Problem Statement:**

Configure a GPIO pin as an output and use timer interrupts to generate square-wave signals at different frequencies. Measure the output frequency and duty cycle using an oscilloscope.

**Frequency Modes:**

| Mode | Frequency |
|---|---:|
| Mode 1 | 100 Hz |
| Mode 2 | 500 Hz |
| Mode 3 | 1 kHz |
| Mode 4 | 2 kHz |
| Mode 5 | 5 kHz |

**Additional Signal Types:**
1. Square Wave
2. Variable Duty-Cycle Wave
3. Pulse Train
4. Burst Signal

**Core Logic:**
1. Configure Timer 0 for periodic interrupts.
2. Toggle the output pin at the required intervals.
3. Change the timer interval or toggle count to generate different frequencies.
4. Use an oscilloscope to observe and measure the generated signals.

### Task 4 – Stepper Motor Speed and Direction Control (Optional)

**Problem Statement:**

Use timer interrupts to generate the stepping sequence for a stepper motor. Control its speed and direction by changing the stepping interval and sequence order.

**Step Sequence:**

1000 → 0100 → 0010 → 0001

**Speed Modes:**

| Speed | Time per Step |
|---|---:|
| Slow | 100 ms |
| Medium | 50 ms |
| Fast | 10 ms |

**Core Logic:**
1. Configure Timer 0 to generate periodic interrupts.
2. Maintain a software counter to track the required step interval.
3. Generate the next step when the counter reaches the selected interval.
4. Change the sequence order to control motor direction.
5. Change the interval to control motor speed.

## CIRCUIT DIAGRAM

![Circuit Diagram](circuit.png)

*Note: Add the actual hardware circuit diagram as `circuit.png` in this CAT5 folder. The LED, output pin, and optional motor-driver connections must match the implemented circuit.*

## CORE LOGIC / PSEUDOCODE / CODE BASE

**General Pseudocode:**

1. Initialize the required GPIO pins.
2. Configure Timer 0 in the required timer mode.
3. Load the timer initial count.
4. Enable Timer 0 interrupt and global interrupt.
5. Start Timer 0.
6. In the timer interrupt service routine:
   - Reload the timer.
   - Update the software time base.
   - Perform the required LED, PWM, pulse-generation, or stepper-motor timing operation.
7. Keep the main program non-blocking and continuously running.

**Code Base:**

- `cat5_task1_timer0_led_toggle.c`
- `cat5_task2_led_fading.c`
- Add the variable-frequency signal-generation source file if implemented.
- Add the stepper-motor source file if implemented.

## INFERENCE

The experiment demonstrates the use of hardware timer interrupts in the AT89S52 microcontroller for accurate and non-blocking timing operations. Timer interrupts are used as a software time base for LED control, software PWM-based fading, variable-frequency signal generation, and optional stepper-motor speed and direction control. The generated signals can be verified using an oscilloscope.