# EXPERIMENT DETAILS

**EXP:** Continuous Lab Evaluation – 7

**DATE:** 24/08/2026 (Week 6)

**NAME OF EXP:** 16x2 LCD Driver Development and Dynamic Display Control

**HARDWARE SETUP / PLATFORM:** AT89S52 (8051) + HD44780-compatible 16x2 Character LCD + 4x4 Matrix Keypad + Embedded C + Keil µVision (Keil C51) + 11.0592 MHz Crystal

---

## TASK NO

### Task 7A – LCD Initialization and Character/String Display

**Problem Statement:**

Develop a 4-bit GPIO-based LCD driver for the AT89S52 using the HD44780-compatible LCD datasheet. Initialize the 16x2 LCD in 4-bit, 2-line mode and display individual characters and strings on both rows.

**Core Logic:**

1. Configure the LCD control and data pins.
2. Initialize the LCD in 4-bit mode.
3. Configure the LCD for 2-line display and 5x8 character font.
4. Implement `lcd_cmd()` to send commands.
5. Implement `lcd_data()` to send character data.
6. Implement `lcd_init()` to initialize the LCD.
7. Display individual characters and strings on both rows.

**Required Functions:**

- `lcd_init()`
- `lcd_cmd()`
- `lcd_data()`

### Task 7B – Cursor Positioning and Dynamic Value Update

**Problem Statement:**

Develop LCD cursor-positioning and data-update functions to display strings and numerical values at specified positions on the 16x2 LCD.

**Core Logic:**

1. Select the required LCD row and column.
2. Set the cursor position using the corresponding DDRAM address.
3. Display strings using the LCD string function.
4. Convert numerical values into displayable characters.
5. Update the displayed values dynamically.

**Required Functions:**

- `lcd_goto(row, column)`
- `lcd_puts(string)`
- `lcd_print_number(value)`

### Task 7C – 4x4 Keypad-Based Character Movement

**Problem Statement:**

Develop an interactive LCD application in which a character moves across the 16x2 LCD based on directional keys pressed on a 4x4 matrix keypad.

**Key Operations:**

| Key | Action |
|---|---|
| 1 | Move Up |
| 2 | Move Down |
| + | Move Left |
| - | Move Right |
| Q |