# ATmega32 Precision Timing & Interrupts

An embedded C project demonstrating bare-metal register configuration, asynchronous hardware interrupts, and precision pulse generation on an ATmega32 AVR microcontroller. This was completed as part of the Microprocessor Laboratory coursework.

## ⚡ Core Implementations
1. **Precision Square Wave:** Timer 1 is configured in Compare Match mode. Given a 1 MHz clock, the 16-bit `OCR1A` register is loaded with `0x01F4` (500) to trigger an Interrupt Service Routine (ISR) exactly every 0.5 ms, generating a highly accurate 1 kHz square wave on pin `PB2`.
2. **Asynchronous Control:** External Interrupt 0 (`INT0`) is configured to catch falling edges from a push-button. Its ISR dynamically toggles the square wave generator on and off without blocking the main CPU execution.
3. **External Event Counting:** Timer 0 is configured as an asynchronous counter, registering physical pulses and displaying the live tally on a $16 \times 2$ Alphanumeric LCD.

## 🔌 Hardware Configuration (Pin Mapping)
Since this project interfaces directly with bare-metal hardware, the microcontroller pins were mapped as follows:

| Component / Function | ATmega32 Pin | Register Configuration |
| :--- | :--- | :--- |
| **Square Wave Output** | `PB2` | Configured as Output (`DDRB = 0x04`) |
| **External Counter Input** | `PB0` (`T0`) | Configured for Timer 0 falling edge |
| **Toggle Push-Button** | `PD2` (`INT0`) | Triggers External Interrupt 0 |
| **LCD Data & Control** | `PORTA` | Handled via `lcd.h` (`_lcd_port=0x1A`) |

## 📁 Repository Structure
* `/part_1_base_system`: Initial implementation featuring a permanent one-way cutoff switch when the interrupt is triggered.
* `/part_2_toggle_upgrade`: Upgraded logic allowing repeatable ON/OFF toggling via the `INT0` hardware interrupt.
* `/legacy_project_files`: Contains the original CodeVisionAVR (`.prj`) configurations and Proteus ISIS (`.pdsprj`) circuit simulation files used during the lab. 

## 🛠️ Software & Tools Used
* **IDE:** CodeVisionAVR (C compiler)
* **Simulation:** Proteus Professional
* **Target Hardware:** 8-bit Microchip ATmega32
