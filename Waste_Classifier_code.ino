#include <CheapStepper.h>
#include <Servo.h>

/* ---------------- PIN DEFINITIONS ---------------- */
const int irPin       = 2;
const int proxPin     = 3;
const int moisturePin = A0;
const int servoPin    = 6;

/* ---------------- STEPPER ---------------- */
// IN1, IN2, IN3, IN4
CheapStepper stepper(8, 10, 9, 11);

/* ---------------- SERVO ---------------- */
Servo flapServo;
const int SERVO_OPEN   = 0;
const int SERVO_CLOSED = 180;


const int METAL_ANGLE = 0;      // 0°
const int DRY_ANGLE   = 120;    // 120°
const int WET_ANGLE   = 240;    // 240°


const int MOISTURE_THRESHOLD = 800;
const unsigned long CLASSIFIER_DELAY_MS = 5000;


unsigned long classifierStartTime;
bool classifierEnabled = false;
bool systemBusy = false;


int lastRotationAngle = 0;

void setup() {
  Serial.begin(9600);

  pinMode(irPin, INPUT_PULLUP);
  pinMode(proxPin, INPUT);

  flapServo.attach(servoPin);
  flapServo.write(SERVO_CLOSED);

  stepper.setRpm(7);   // torque-safe speed

  Serial.println("Power ON");
  Serial.println("System initializing...");

  delay(3000);

  classifierStartTime = millis();
  Serial.println("Waiting before enabling classifier...");
}


// Moisture averaging
int getMoistureValue() {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += analogRead(moisturePin);
    delay(10);
  }
  return sum / 5;
}

// Servo operation
void operateFlap() {
  flapServo.write(SERVO_OPEN);
  delay(1800);
  flapServo.write(SERVO_CLOSED);
  delay(600);
}

// Stable metal detection
bool metalDetected() {
  if (digitalRead(proxPin) == HIGH) {
    delay(150);
    return digitalRead(proxPin) == HIGH;
  }
  return false;
}


void returnToMetal() {
  if (lastRotationAngle > 0) {
    stepper.moveDegrees(false, lastRotationAngle); // CCW return
    delay(300);
    lastRotationAngle = 0;
  }
}


void loop() {

 
  if (!classifierEnabled) {
    if (millis() - classifierStartTime >= CLASSIFIER_DELAY_MS) {
      classifierEnabled = true;
      Serial.println("Classifier ACTIVE");
    }
    return;
  }


  if (!systemBusy && metalDetected()) {

    systemBusy = true;
    Serial.println("Metal detected");

    // METAL is at 0°, so no rotation needed
    lastRotationAngle = METAL_ANGLE;

    operateFlap();

    returnToMetal();   // does nothing (already at 0°)

    while (digitalRead(proxPin) == HIGH) delay(50);
    systemBusy = false;

    Serial.println("Metal Done\n");
  }

 
  if (!systemBusy && digitalRead(irPin) == LOW) {

    systemBusy = true;
    delay(350);

    int moisture = getMoistureValue();

    if (moisture < MOISTURE_THRESHOLD) {
      Serial.println("Wet waste");
      stepper.moveDegrees(true, WET_ANGLE);   // CW
      lastRotationAngle = WET_ANGLE;
    } else {
      Serial.println("Dry waste");
      stepper.moveDegrees(true, DRY_ANGLE);   // CW
      lastRotationAngle = DRY_ANGLE;
    }

    delay(500);
    operateFlap();

    returnToMetal();   // CCW return by same angle

    while (digitalRead(irPin) == LOW) delay(50);
    systemBusy = false;

    Serial.println("Wet/Dry Done\n");
  }
}