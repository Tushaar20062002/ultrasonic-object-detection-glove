
#include <NewPing.h>

#define TRIGGER_PIN 11
#define ECHO_PIN 10
#define MAX_DISTANCE 200

#define MOTOR_PIN 7
#define BUZZER_PIN 8

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int distance = 0;
unsigned long previousMillis = 0;
const long interval = 500;

void initializePins() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void readDistance() {
  distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void giveFeedback(int distance) {
  if (distance > 0 && distance < 100) {
    digitalWrite(MOTOR_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(MOTOR_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void setup() {
  initializePins();
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    readDistance();
    giveFeedback(distance);
  }
}
