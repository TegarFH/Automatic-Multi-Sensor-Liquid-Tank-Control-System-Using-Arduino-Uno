#include <LiquidCrystal.h>
#include <Servo.h>

// --- LCD 16x2 ---  (PIN TETAP)
LiquidCrystal lcd(7, 6, 5, 8, 11, 12);

// --- PIN SENSOR --- (TETAP)
#define TMP36_PIN A0
#define POT_PIN A1
#define TRIG 9
#define ECHO 10

// --- PIN AKTUATOR --- (TETAP)
#define MOTOR_PIN 3
#define ALARM_PIN 4   

// --- PIN SERVO ---
#define SERVO_PIN 2
Servo valveServo;

// --- BATAS SISTEM ---
float highTemp = 40.0;
float pressureLimit = 0.8;  
int lowLevel = 138;

const float tankHeight = 200.0;   
const float tankVolume = 16000.0; 

// ========== Variabel untuk Hysteresis Motor ==========
bool motorState = false;   // false = OFF, true = ON


// =================================================================
// Fungsi Baca Ultrasonic
// =================================================================
float readDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000); // timeout 30ms

  if (duration == 0) return -1;
  float distance = duration * 0.034 / 2;

  if (distance <= 0 || distance > 400) return -1;
  return distance;
}

// =================================================================
// Fungsi Baca TMP36
// =================================================================
float readTemperature() {
  int value = analogRead(TMP36_PIN);
  float voltage = value * (5.0 / 1023.0);
  float tempC = (voltage - 0.5) * 100.0;

  if (tempC < -10 || tempC > 150) return -999;
  return tempC;
}

// =================================================================
// Tampilan Error
// =================================================================
void showError(String msg) {
  digitalWrite(MOTOR_PIN, LOW);
  digitalWrite(ALARM_PIN, LOW);
  valveServo.write(0);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" SENSOR ERROR ");
  lcd.setCursor(0,1);
  lcd.print(msg);

  Serial.println("ERROR: " + msg);
  delay(1000);
}

// =================================================================
// Setup
// =================================================================
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  lcd.print("SYSTEM ONLINE");
  delay(1000);
  lcd.clear();

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(ALARM_PIN, OUTPUT);

  valveServo.attach(SERVO_PIN);
  valveServo.write(0);
}

// =================================================================
// Loop
// =================================================================
void loop() {

  float temperature = readTemperature();
  float distance = readDistance();
  int potValue = analogRead(POT_PIN);
  float pressure = potValue / 1023.0;

  if (temperature == -999) { showError("TEMP FAIL"); return; }
  if (distance == -1) { showError("LEVEL FAIL"); return; }
  if (potValue == 0 || potValue == 1023) { showError("PRESS FAIL"); return; }

  float waterHeight = tankHeight - distance;
  if (waterHeight < 0) waterHeight = 0;
  if (waterHeight > tankHeight) waterHeight = tankHeight;

  float waterLiter = (waterHeight / tankHeight) * tankVolume;

  // ============================================================
  //   KONTROL MOTOR DENGAN HYSTERESIS
  // ============================================================
  
  if (distance > 20) {
    motorState = true;     // Nyalakan motor
  } 
  else if (distance < 5) {
    motorState = false;    // Matikan motor
  }

  // Terapkan status motor
  digitalWrite(MOTOR_PIN, motorState ? HIGH : LOW);


  // ============================================================

  // ------------------ Alarm ------------------
  if (temperature > highTemp || pressure > pressureLimit)
    digitalWrite(ALARM_PIN, HIGH);
  else
    digitalWrite(ALARM_PIN, LOW);

  // ------------------ Servo Tekanan ------------------
  if (pressure > pressureLimit) valveServo.write(90);
  else valveServo.write(0);

  // ------------------ Tampilan LCD ------------------
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(temperature,1);
  lcd.print("C ");

  lcd.print("P:");
  lcd.print((int)(pressure * 100));
  lcd.print("%");

  lcd.setCursor(0,1);
  lcd.print("V:");
  lcd.print(waterLiter,0);
  lcd.print("L ");

  if (pressure > pressureLimit) lcd.print("VAL");
  else lcd.print(motorState ? " ON " : "OFF");

  // ------------------ Debug Serial ------------------
  Serial.print("Temp: "); Serial.print(temperature);
  Serial.print(" C | Dist: "); Serial.print(distance);
  Serial.print(" cm | Vol: "); Serial.print(waterLiter);
  Serial.print(" L | Pressure: ");
  Serial.println(pressure * 100);

  delay(500);
}
