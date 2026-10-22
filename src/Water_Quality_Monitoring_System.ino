#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Water Quality Monitoring System - Arduino Uno/Nano
// pH analog output: A0 | TDS analog output: A1
// LCD I2C: 0x27 (some modules use 0x3F)
// Green LED: D6 | Red LED: D7 | Buzzer: D8
// IMPORTANT: Calibrate the pH and TDS sensors before relying on readings.

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int PH_PIN = A0, TDS_PIN = A1;
const int GREEN_LED = 6, RED_LED = 7, BUZZER = 8;
const float VREF = 5.0;
const int SAMPLES = 30;
const float PH_LOW = 6.5, PH_HIGH = 8.5, TDS_LIMIT = 500.0;

// EXAMPLE VALUES ONLY: replace with measured calibration voltages.
float V_PH7 = 2.50;
float V_PH4 = 3.05;
float temperatureC = 25.0; // fixed reference; no temperature sensor is connected

float readAverageVoltage(int pin) {
  unsigned long sum = 0;
  for (int i = 0; i < SAMPLES; i++) {
    sum += analogRead(pin);
    delay(10);
  }
  return (sum / (float)SAMPLES) * VREF / 1023.0;
}

float voltageToPH(float v) {
  float denominator = V_PH7 - V_PH4;
  if (abs(denominator) < 0.0001) return 7.0;
  float slope = (7.00 - 4.01) / denominator;
  return 7.00 + slope * (v - V_PH7);
}

float voltageToTDS(float v) {
  float compensation = 1.0 + 0.02 * (temperatureC - 25.0);
  if (compensation <= 0.0) compensation = 1.0;
  float cv = v / compensation;
  float ppm = (133.42 * cv * cv * cv - 255.86 * cv * cv + 857.39 * cv) * 0.5;
  return ppm < 0.0 ? 0.0 : ppm;
}

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("Water Quality");
  lcd.setCursor(0, 1); lcd.print("Monitor Ready");
  delay(1800);
  lcd.clear();
}

void loop() {
  float phVoltage = readAverageVoltage(PH_PIN);
  float tdsVoltage = readAverageVoltage(TDS_PIN);
  float ph = voltageToPH(phVoltage);
  float tds = voltageToTDS(tdsVoltage);
  bool phBad = (ph < PH_LOW || ph > PH_HIGH);
  bool tdsBad = (tds > TDS_LIMIT);
  bool warning = phBad || tdsBad;

  lcd.setCursor(0, 0);
  lcd.print("pH:"); lcd.print(ph, 1);
  lcd.print(phBad ? " BAD " : " OK  ");
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print("TDS:"); lcd.print((int)tds); lcd.print("ppm ");
  lcd.print(tdsBad ? "BAD" : "OK ");
  lcd.print(" ");

  if (warning) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    tone(BUZZER, 2000, 300);
  } else {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    noTone(BUZZER);
  }

  Serial.print("pH voltage="); Serial.print(phVoltage, 3);
  Serial.print(" V, pH="); Serial.print(ph, 2);
  Serial.print(", TDS voltage="); Serial.print(tdsVoltage, 3);
  Serial.print(" V, TDS="); Serial.print(tds, 1);
  Serial.print(" ppm, status=");
  Serial.println(warning ? "CHECK WATER" : "WITHIN SET LIMITS");
  delay(1000);
}
