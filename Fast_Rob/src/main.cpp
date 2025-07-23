#include <Arduino.h>
#include <stdint.h>
#include <L298.h>
#include <HCSR04.h>
#include "IR08H.h"
#include "HW201.h"
#include "../lib/config.h"

// UltraSonicDistanceSensor distanceSensor(7, 8);  // Initialize sensor that uses digital pins 13 and 12.
HW201 ir_middle(ir_middle_pin);  // Initialize IR08H sensor on pin 6 with enable pin 9.
HW201 ir_left(ir1_pin);
HW201 ir_right(ir2_pin);

IR08H obs(obstacle_pin);
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
  // motor.moveForward(125);  // Move forward at full speed
  if (obs.readValue() == 0) {  // If an obstacle is detected
    // motor.stop();  // Stop the motors
    Serial.println("Obstacle detected, stopping motors");
    delay(1000);  // Wait for a second before checking again
    return;  // Exit the loop to avoid further actions
  }
  if(ir_middle.readValue() == 1) {  
    // motor.moveForward(125);  // Stop the motors
    Serial.println("Moving foward");
  }
  else if(ir_left.readValue() == 1) {
    // motor.turnLeft(125);  // Turn left at full speed
    Serial.println("Turning left");
    
  } 
  else if(ir_right.readValue() == 1) {
    Serial.println("Turning right");
  }
  
  // motor.moveForward(125);  // Move forward at full speed
}

// put function definitions here: