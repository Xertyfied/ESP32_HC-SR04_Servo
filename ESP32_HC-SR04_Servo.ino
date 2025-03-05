#include <Arduino.h>
#include <ESP32Servo.h>  // Use ESP32-compatible servo library

#define TRIG_PIN 5
#define ECHO_PIN 18
#define SERVO_PIN 16

Servo myServo;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  myServo.attach(SERVO_PIN); // Attach servo to the ESP32-S3
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 50) distance = 50;
  if (distance < 2) distance = 2;

  int servoAngle = map(distance, 2, 50, 180, 0);
  myServo.write(servoAngle);

  delay(100);
}
