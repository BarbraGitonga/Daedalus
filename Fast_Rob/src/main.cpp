#include <Arduino.h>
#include <stdint.h>
#include <L298.h>
#include <HCSR04.h>
#include "IR08H.h"

IR08H ir(6, 9);  // Initialize IR08H sensor on pin 6 with enable pin 9.
// UltraSonicDistanceSensor distanceSensor(7, 8);  // Initialize sensor that uses digital pins 13 and 12.

uint8_t in1 = 2;  // Pin for IN1 control
uint8_t in2 = 3;  // Pin for IN2 control
uint8_t enA = 0;  // Pin for ENA control
uint8_t in3 = 4;  // Pin for IN3 control
uint8_t in4 = 5;  // Pin for IN4 control
uint8_t enB = 1;  // Pin for ENB control
L298Pins motorPins = {in1, in2, enA, in3, in4, enB};
L298 motor(motorPins);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  motor.begin();  // Initialize the motor driver pins
  Serial.println("L298 Motor Driver Initialized");
  ir.begin();  // Initialize the IR08H sensor
}

void loop() {
  // Serial.println(distanceSensor.measureDistanceCm());
  delay(500);
  // put your main code here, to run repeatedly:

  if(ir.readValue() == 0) {  // If an obstacle is detected within 100 units
    motor.stop();  // Stop the motors
    delay(1000);  // Wait for 1 second
    motor.reverse(125);  // Reverse at full speed
    delay(1000);
  } 
  
  motor.moveForward(125);  // Move forward at full speed
  delay(2000);  // Wait for 2 seconds
}

// put function definitions here: