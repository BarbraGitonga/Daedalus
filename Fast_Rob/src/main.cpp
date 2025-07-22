#include <Arduino.h>
#include <stdint.h>
#include <L298.h>
#include <HCSR04.h>
#include "IR08H.h"
#include "HW201.h"
#include "../lib/config.h"

IR08H ir_middle(ir_middle_pin, ir_middle_enable_pin);  // Initialize IR08H sensor on pin 6 with enable pin 9.
// UltraSonicDistanceSensor distanceSensor(7, 8);  // Initialize sensor that uses digital pins 13 and 12.
HW201 ir_left(ir1_pin);
HW201 ir_right(ir2_pin);

L298Pins motorPins = {in1, in2, enA, in3, in4, enB};
L298 motor(motorPins);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  motor.begin();  // Initialize the motor driver pins
  Serial.println("L298 Motor Driver Initialized");
  ir_middle.begin();  // Initialize the IR08H sensor
  ir_left.begin();  // Initialize the first HW201 sensor
  ir_right.begin();  // Initialize the second HW201 sensor
}

void loop() {
  // Serial.println(distanceSensor.measureDistanceCm());
  delay(500);
  // put your main code here, to run repeatedly:

  if(ir_middle.readValue() == 0) {  // If an obstacle is detected within 100 units
    motor.moveForward(125);  // Stop the motors
    delay(1000);
  } else if(ir_left.readValue() == 1) {
    motor.turnLeft(125);  // Turn left at full speed
    delay(1000);
  } else if(ir_right.readValue() == 1) {
    motor.turnRight(125);  // Turn right at full speed
    delay(1000);
  } 
  
  motor.moveForward(125);  // Move forward at full speed
  delay(2000);  // Wait for 2 seconds
}

// put function definitions here: