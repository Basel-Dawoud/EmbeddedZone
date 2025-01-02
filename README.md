# Stop Watch System

## Overview
This repository contains the code and documentation for a Stop Watch system implemented using the ATmega32 microcontroller. The project utilizes Timer1 in CTC (Clear Timer on Compare Match) mode and a multiplexed six 7-segment display to count and display elapsed time in hours, minutes, and seconds.

### Features
- **Multiplexed Display**: Efficiently displays time on six 7-segment displays using a multiplexing technique.
- **External Interrupts**: 
  - **Reset**: Clears the timer and resets the stopwatch.
  - **Pause**: Stops the timer.
  - **Resume**: Restarts the timer from the paused state.
- **Timer1 in CTC Mode**: Provides precise timing functionality for the stopwatch.

---

## System Design

### Hardware Requirements
1. **ATmega32 Microcontroller**
2. **Six 7-Segment Displays**
3. **Three Push Buttons**:
   - **Reset** (connected to INT0)
   - **Pause** (connected to INT1)
   - **Resume** (connected to INT2)
4. **Resistors and Connecting Wires**
5. **Power Supply** (5V)

### Software
The system is programmed in **C** using AVR libraries, leveraging interrupts and timer functionalities for accurate timekeeping.

---

## File Descriptions

### `StopWatch.c`
- Contains the main program logic and interrupt service routines.
- Implements:
  - Timer1 initialization in CTC mode.
  - Interrupt Service Routines for Reset (INT0), Pause (INT1), and Resume (INT2).
  - Multiplexing logic for 7-segment displays.

### Key Functions
- **`Timer1_Init_CTC_Mode()`**: Configures Timer1 in CTC mode with a compare value of 1024.
- **Interrupt Service Routines (ISRs)**:
  - **TIMER1_COMPA_vect**: Increments the time ticks.
  - **INT0_vect**: Resets the stopwatch.
  - **INT1_vect**: Pauses the stopwatch.
  - **INT2_vect**: Resumes the stopwatch.

---

## How to Use

### Setup
1. Connect the hardware components as specified in the system design.
2. Compile and upload the `StopWatch.c` code to the ATmega32 microcontroller using an appropriate programmer (e.g., USBasp).

### Operation
- Press the **Reset** button to start from 0:00:00.
- Press the **Pause** button to stop the timer.
- Press the **Resume** button to continue counting.

---

## Additional Information

### Timer Configuration
The stopwatch is based on Timer1, operating in CTC mode with a compare value (`COMP`) of 1024. The timer tick duration is adjusted for accuracy by configuring the prescaler and compare value.

### Display Multiplexing
The 7-segment displays are driven using a multiplexing technique to reduce hardware requirements. Only one segment is active at any given time, with rapid switching to create the illusion of simultaneous display.

---

## Future Enhancements
- Add support for lap timing.
- Integrate an external display for larger viewing.
- Include EEPROM storage for saving elapsed time.

---

## Author
**Basel Dawoud**  
*Contact*: baseldawoud2003@gmail.com  
