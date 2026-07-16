# Bare-Metal ATmega32: Precision Timing & Interrupts

This repository contains my implementation for **Experiment 3** of the Microprocessor Laboratory course during my Bachelor's degree. The project focuses on bare-metal register configuration, asynchronous hardware interrupts, and deterministic pulse generation on an ATmega32 AVR microcontroller.

## System Architecture & Core Logic

### 1. Precision Square Wave Generation (Timer 1)
Instead of relying on blocking software delay functions, this system utilizes **Timer 1** in Output Compare Match mode to generate a precise **1 kHz** square wave, freeing up the ALU for other tasks. 
* **The Math:** With a system clock of **1 MHz** and no prescaling (`TCCR1B = 0x01`), the timer increments every **1 µs**. To toggle the pin every **0.5 ms** (creating a **1 ms** full period), the target tick count is **500**.
* **Register Setup:** The 16-bit Output Compare Register (`OCR1A`) is loaded with `0x01F4` (**500** in decimal). When `TCNT1` matches this value, a hardware interrupt (`TIM1_COMPA`) is triggered to toggle the output pin.

### 2. Asynchronous Control (External Interrupt 0)
The system must respond immediately to user input without constantly polling a pin state.
* **Configuration:** External Interrupt 0 (`INT0`) is enabled and configured to trigger on the falling edge of the signal (`MCUCR = 0x02`). 
* **State Toggling:** The Interrupt Service Routine (ISR) executes dynamically to toggle a `pulse_enable` state flag. This guarantees an immediate response to the push-button without halting the main execution loop.

### 3. External Event Counting (Timer 0)
**Timer 0** is disconnected from the internal clock and configured as an asynchronous counter (`TCCR0 = 0x06`). It registers physical pulses on the external `T0` pin, incrementing its internal register (`TCNT0`) on every falling edge. The live tally is continuously polled in the main loop and pushed to a **16x2 Alphanumeric LCD**.

## Hardware Mapping & Register Setup

| Peripheral | ATmega32 Pin | Register Setup | Function |
| :--- | :--- | :--- | :--- |
| **Pulse Output** | `PB2` | `DDRB = 0x04` | Toggles state via Timer 1 ISR |
| **Counter Input** | `PB0` (`T0`) | `TCCR0 = 0x06` | Triggers Timer 0 on falling edge |
| **Control Button** | `PD2` (`INT0`) | `MCUCR = 0x02`, `GICR \|= 0x40` | Triggers INT0 ISR |
| **LCD Bus** | `PORTA` | `_lcd_port=0x1A` | Handles parallel display data |

## Repository Structure
* `/part_1_base_system`: Initial lab implementation featuring a permanent one-way cutoff switch when the interrupt is triggered. Original CodeVisionAVR (`.prj`) configurations and Proteus ISIS (`.pdsprj`) circuit simulation workspaces used during the lab.
* `/part_2_toggle_upgrade`: Upgraded logical flow allowing repeatable ON/OFF toggling via the `INT0` hardware interrupt. Original CodeVisionAVR (`.prj`) configurations and Proteus ISIS (`.pdsprj`) circuit simulation workspaces used during the lab. 

## Toolchain
* **Target Hardware:** 8-bit Microchip ATmega32
* **Firmware:** Embedded C (compiled via CodeVisionAVR)
* **Simulation:** Proteus Professional
