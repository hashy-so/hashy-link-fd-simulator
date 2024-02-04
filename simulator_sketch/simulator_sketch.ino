#include <Arduino.h>

const int pinCondenser = 16;
const int pinVacuum = 15;
const int pinHeater = 14;
const int pinDrain = 21;
const int pinSpare = 19;

const int pinThermistor2 = 25;
const int pinPressure = 26;

const int pinBuzzer = 5;

void setup() {
  Serial.begin(115200);

  pinMode(pinCondenser, OUTPUT);
  pinMode(pinVacuum, OUTPUT);
  pinMode(pinHeater, OUTPUT);
  pinMode(pinDrain, OUTPUT);
  pinMode(pinSpare, OUTPUT);

  pinMode(pinThermistor2, OUTPUT);
  pinMode(pinPressure, OUTPUT);

  pinMode(pinBuzzer, OUTPUT);
}

int voltageToDACValue(float voltage) {
  return (int)(voltage / 3.3 * 255);
}

void executeCommand(String command) {
  if (command.startsWith("-H") || command.startsWith("-V") || command.startsWith("-C") || command.startsWith("-R") || command.startsWith("-S")) {
    int pin = command.startsWith("-C") ? pinCondenser : 
              command.startsWith("-V") ? pinVacuum : 
              command.startsWith("-H") ? pinHeater : 
              command.startsWith("-D") ? pinDrain : pinSpare;
    int state = command.charAt(3) == '1' ? HIGH : LOW;

    digitalWrite(pin, state);

    Serial.println("Set " + command.substring(0, 2) + " to " + (state == HIGH ? "ON" : "OFF"));
  } else if (command.startsWith("-TV") || command.startsWith("-PV")) {
    float voltage = command.substring(3).toFloat();
    int dacValue = voltageToDACValue(voltage);
    int pin = command.startsWith("-TV") ? pinThermistor2 : pinPressure;

    dacWrite(pin, dacValue);

    Serial.println("Set " + command.substring(0, 3) + " to " + String(voltage) + "V");
  } else if (command.startsWith("-B")) {
    int numFallingEdges = command.substring(2).toInt(); 
    triggerBuzzerEvent(numFallingEdges);
    Serial.println("Triggered Buzzer with " + String(numFallingEdges) + " falling edges");
  }
}

void triggerBuzzerEvent(int numToggles) {
  for (int i = 0; i < numToggles; ++i) {
    digitalWrite(pinBuzzer, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinBuzzer, LOW);
    delayMicroseconds(10);
  }
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    executeCommand(command);
  }
}
