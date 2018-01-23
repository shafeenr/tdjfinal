#include <AFMotor.h>
#include <Servo.h>

class LED {
    int ledPin;
    int ledState;
    long onTime;
    long offTime;

    unsigned long previousMillis;

  public:
    LED (int pin, long on, long off) {
      ledPin = pin;
      pinMode(ledPin, OUTPUT);

      onTime = on;
      offTime = off;

      ledState = LOW;
      previousMillis = 0;
    }

    void Update() {
      unsigned long currentMillis = millis();

      if ((ledState == HIGH) && (currentMillis - previousMillis >= onTime))
      {
        ledState = LOW;
        previousMillis = currentMillis;
        digitalWrite(ledPin, ledState);
      }
      else if ((ledState == LOW) && (currentMillis - previousMillis >= offTime))
      {
        ledState = HIGH;
        previousMillis = currentMillis;
        digitalWrite(ledPin, ledState);
      }
    }

    void ledOff() {
      digitalWrite(ledState, LOW);
    }
};

LED railWarnings(13, 350, 50);
LED ferrisWheelLights(5, 350, 10);

AF_DCMotor railArmOne(1, MOTOR12_64KHZ);
AF_DCMotor railArmTwo(2, MOTOR12_64KHZ);

Servo ferrisWheel;

void setup() {
   ferrisWheel.attach(2);
}

void loop() {
  railArmOne.setSpeed(255);
  railArmTwo.setSpeed(255);
  railArmOne.run(BACKWARD);
  railArmTwo.run(FORWARD);
  railWarnings.Update();
  delay(1500);
  railArmOne.run(RELEASE);
  railArmTwo.run(RELEASE);

  ferrisWheel.writeMicroseconds(1700);
  ferrisWheelLights.Update();
  railWarnings.Update();
  delay(5000);
  ferrisWheelLights.ledOff();
  railWarnings.ledOff();

  railArmOne.setSpeed(255);
  railArmTwo.setSpeed(255);
  railArmOne.run(FORWARD);
  railArmTwo.run(BACKWARD);
  delay(1900);
  railArmOne.run(RELEASE);
  railArmTwo.run(RELEASE);
  delay(5000);
}
