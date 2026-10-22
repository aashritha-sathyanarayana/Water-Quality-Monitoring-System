# Wiring and Calibration

## Pin map
- pH analog output -> A0
- TDS analog output -> A1
- I2C LCD SDA -> A4 and SCL -> A5 on Arduino Uno/Nano
- Green LED through 220 ohm resistor -> D6
- Red LED through 220 ohm resistor -> D7
- Buzzer signal/positive -> D8
- Join grounds; use module-specific supply voltages.

## pH calibration
1. Allow the module to stabilize.
2. Place the probe in pH 7.00 buffer and record its stable output voltage.
3. Rinse the probe, place it in pH 4.01 buffer, and record the stable output voltage.
4. Replace `V_PH7` and `V_PH4` in the sketch with measured values.
5. Follow the probe manufacturer's cleaning and storage instructions.

## TDS calibration
TDS conversion depends on the sensor module. Check its documentation and compare the reading with a suitable standard solution. The sketch currently assumes 25 C and uses a commonly used analog TDS polynomial.

## Troubleshooting
- Blank LCD: check SDA/SCL, power, contrast, and I2C address (`0x27` or `0x3F`).
- Unstable readings: check connections, let probes settle, and ensure the sensor boards are powered correctly.
- Incorrect pH: recalibrate using fresh buffer solutions.
- Incorrect TDS: verify module-specific conversion and calibration.
- LED/buzzer issue: check polarity, resistor, pin numbers, and common ground.
