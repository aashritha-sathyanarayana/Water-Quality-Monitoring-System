# Water Quality Monitoring System

An Arduino-based mini project that measures pH and estimated Total Dissolved Solids (TDS), displays readings on a 16x2 I2C LCD, and alerts the user with LEDs and a buzzer when readings exceed configured limits.

## Features
- Analog pH and TDS readings
- Averaging of 30 sensor samples
- Live LCD display and Serial Monitor output
- Green LED for readings within configured limits
- Red LED and buzzer when either threshold is exceeded

## Hardware
- Arduino Uno/Nano
- Analog pH sensor module and probe
- Analog TDS sensor module
- 16x2 LCD with I2C backpack
- Green and red LEDs, each with a 220 ohm resistor
- 5 V buzzer, breadboard, jumper wires, USB power

## Wiring

| Component | Arduino pin |
|---|---|
| pH sensor analog output | A0 |
| TDS sensor analog output | A1 |
| LCD SDA / SCL | A4 / A5 (Uno/Nano) |
| Green LED anode via 220 ohm resistor | D6 |
| Red LED anode via 220 ohm resistor | D7 |
| Buzzer signal/positive | D8 |
| Grounds | GND |

Power sensor modules according to their own voltage specifications and connect grounds together.

## Setup
1. Install the Arduino IDE: https://www.arduino.cc/en/software
2. Install the `LiquidCrystal_I2C` library from Library Manager.
3. Open `src/Water_Quality_Monitoring_System.ino`.
4. Select your board and serial port, then upload.
5. Open Serial Monitor at **9600 baud**.
6. If the LCD is blank, verify wiring and try I2C address `0x3F` instead of `0x27`.

## Calibration
The pH calibration voltages in the sketch (`V_PH7` and `V_PH4`) are examples only. Measure the sensor output in pH 7.00 and pH 4.01 buffer solutions and replace the values. For TDS, verify the conversion against your sensor documentation and a suitable standard solution. The code assumes 25 C because a temperature sensor is not connected.

## Decision thresholds
- pH: 6.5 to 8.5
- TDS: 500 ppm
These are configurable screening thresholds, not a certification of drinking-water safety.

## Repository structure
- `src/` — Arduino source code
- `docs/` — wiring/calibration notes and project report
- `images/` — add prototype photos here
- `CONTRIBUTORS.md` — team list

## Limitations
This system only screens pH and estimated TDS. It does not detect bacteria, heavy metals, pesticides, or all contaminants. A reading within limits does not prove water is safe to drink; certified laboratory testing is needed where safety matters.
