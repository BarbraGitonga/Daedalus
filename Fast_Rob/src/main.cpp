#include <Arduino.h>
#include <stdint.h>
#include <L298.h>

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
  
}

void loop() {
  // put your main code here, to run repeatedly:
  motor.moveForward(255);  // Move motors forward at full speed
  Serial.println("Moving Forward");
  delay(2000);  // Wait for 2 seconds
  motor.reverse(255);  // Move motors backward at full speed
  Serial.println("Reversing");
  delay(2000);  // Wait for 2 seconds
  motor.turnLeft(255);  // Turn right at full speed
  Serial.println("Turning Right");
  delay(2000);  // Wait for 2 seconds
  motor.turnRight(255);  // Turn left at full speed
  Serial.println("Turning Left");
  delay(2000);  // Wait for 2 seconds
  motor.stop();  // Stop the motors
  Serial.println("Motors Stopped");
  delay(2000);  // Wait for 2 seconds before repeating
  motor.moveForward(128);  // Move motors forward at half speed 
  Serial.println("Moving Forward at Half Speed");
  delay(2000);  // Wait for 2 seconds
  motor.reverse(128);  // Move motors backward at half speed
  delay(2000);  // Wait for 2 seconds
}

// put function definitions here: