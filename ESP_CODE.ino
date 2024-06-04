#define BLYNK_TEMPLATE_ID           "TMPL61h0AooTF"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "LxTJ-5uaHH_Qyp5X94a0SgmNyKeplKXF"

#include <AccelStepper.h>
#include <BlynkSimpleEsp32.h>

const char auth[] = BLYNK_AUTH_TOKEN;         // Blynk authentication token
const char ssid[] = "MLK iPhone";         // Your WiFi SSID
const char pass[] = "Zz112344";     // Your WiFi password

const int speedPin = 2;    // Variable that control the speed of fan
const int LEDPin = 22;     // Variable that control the LED
const int FANPowerPin = 4; // Variable that switch pn/off fan


int currentPosition = 0;   // Variable that keep track the curnt position of the motor
#define UPPER_LIMIT 13500  // Maximum upper limit
#define LOWER_LIMIT 0      // Maximum lower limit

// Flags indicator
bool clockwiseFlag = false;         
bool counterclockwiseFlag = false;

// ULN2003 Motor Driver Pins
#define IN1 5
#define IN2 18
#define IN3 19
#define IN4 21

// Blynk virtual pins for the buttons
#define buttonClockwisePin V1         // Down
#define buttonCounterclockwisePin V0  // Up
#define buttonStepperOFFPin V3  // Up
#define LED V4                        // Led
#define FAN V2                        // FAN

// initialize the stepper library
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(LEDPin, OUTPUT);
  pinMode(speedPin, OUTPUT);
  pinMode(FANPowerPin, OUTPUT);  
  // set the speed and acceleration
  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(1000);
}

void loop() {
  Blynk.run();
  // Move the stepper motor (one step at a time)
  stepper.runSpeed();
    if (clockwiseFlag) {
    if (currentPosition < UPPER_LIMIT) {
      stepper.setSpeed(-1000);   // Set speed for clockwise rotation
      stepper.enableOutputs();  // Enable motor outputs
      stepper.runSpeed();       // Move the motor
      delay(2);
      currentPosition++;
    } else {
      stepper.setSpeed(0);       // Set speed to 0 to stop the motor
      stepper.disableOutputs();  // Disable motor outputs
    }
  } if (counterclockwiseFlag) {
    if (currentPosition > LOWER_LIMIT) {
      stepper.setSpeed(1000);  // Set speed for counterclockwise rotation
      stepper.enableOutputs();  // Enable motor outputs
      stepper.runSpeed();       // Move the motor
      delay(2);
      currentPosition--;
    } else {
      stepper.setSpeed(0);       // Set speed to 0 to stop the motor
      stepper.disableOutputs();  // Disable motor outputs
    }
  } if(counterclockwiseFlag == false && clockwiseFlag == false) {
      stepper.setSpeed(0);       // Set speed to 0 to stop the motor
      stepper.disableOutputs();  // Disable motor outputs
    }
}

BLYNK_WRITE(buttonClockwisePin) {
  // Set incoming value from pin V4 to a variable
  int buttonClockwiseState = param.asInt();
  if (buttonClockwiseState == HIGH) {
    clockwiseFlag = true;
    counterclockwiseFlag = false;
  } else {
    clockwiseFlag = false;
  }
}

BLYNK_WRITE(buttonCounterclockwisePin) {
  // Set incoming value from pin V1 to a variable
  int buttonCounterclockwiseState = param.asInt();
  if (buttonCounterclockwiseState == HIGH) {
    counterclockwiseFlag = true;
    clockwiseFlag = false;
  } else {
    counterclockwiseFlag = false;
  }
}

BLYNK_WRITE(buttonStepperOFFPin) {
  // Set incoming value from pin V1 to a variable
  int buttonStepperOFFState = param.asInt();
  if (buttonStepperOFFState == HIGH) {
    clockwiseFlag = false;
    counterclockwiseFlag = false;
    stepper.setSpeed(0);       // Set speed to 0 to stop the motor
    stepper.disableOutputs();  // Disable motor outputs
  } 
}
BLYNK_WRITE(LED) {
  // Set incoming value from pin V4 to a variable
  int value = param.asInt();
  digitalWrite(LEDPin, value);
}

BLYNK_WRITE(FAN){
  // Set incoming value from pin V2 to a variable
int value = param.asInt();
 if(value <= 0){
  digitalWrite(FANPowerPin, LOW);
 }
 else{
  digitalWrite(FANPowerPin, HIGH);
  // Set the fan speed using PWM
  analogWrite(speedPin, value);
 }
}