#include <Arduino.h>
#include <stdint.h>
#include <L298.h>
#include <HCSR04.h>
#include "IR08H.h"
#include "HW201.h"
#include "../lib/config.h"
#include "PID.h"

enum State {
  LINE_FOLLOWING,
  MAZE_SOLVING,
  RESCUE,
  COMPLETE
};

State currentState = LINE_FOLLOWING;
volatile bool obs_flag = false;
volatile bool object = false;
unsigned long lineLostTime = 0;

HW201 ir_middle(ir_middle_pin);
HW201 ir_left(ir_left_pin);
HW201 ir_right(ir_right_pin);
IR08H obs(obstacle_pin);

L298Pins motorPins = {in1, in2, enA, in3, in4, enB};
L298 motor(motorPins);
int baseSpeed = 200; // Base speed for the motors

double kp = 1.0; // Proportional gain
double ki = 0.1; // Integral gain
double kd = 0.01; // Derivative gain
int weights[] = {-2, 0, 2}; // Line sensor array weights
int sensor_number = sizeof(weights) / sizeof(weights[0]); // Number of sensors
PID pidController(kp, ki, kd, weights, sensor_number); // Initialize PID controller with example values
// Interrupt handler
void obstacleDetected() {
  obs_flag = true;
}

void objectDetected(){
  object = true;
}

void handleLineFollowing(){
  bool leftValue = ir_left.isLine();
  bool rightValue = ir_right.isLine();
  bool middleValue = ir_middle.isLine();

  if(!leftValue && !rightValue && !middleValue) {
    if (lineLostTime == 0) {
      lineLostTime = millis(); // Start the timer when line is lost
    } else if (millis() - lineLostTime > 2000) { // If line is lost for more than 2 seconds
      Serial.println("Line lost for too long, switching to MAZE_SOLVING state.");
      motor.stop(); // Stop the motors
      lineLostTime = 0; // Reset the timer
      currentState = MAZE_SOLVING; // Switch to maze solving state
      Serial.print("Switching to state: ");
      Serial.println(stateToString(currentState));
      return;
    }
  }

  int sensors[] = {leftValue, middleValue, rightValue};

  double correction = pidController.compute(sensors);
  int leftSpeed = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;
  if (leftSpeed < 0) leftSpeed = 0; // Ensure speed is not negative
  if (rightSpeed < 0) rightSpeed = 0; // Ensure speed is  not negative
  motor.setSpeed(leftSpeed, rightSpeed);
}

// void handleLineFollowing() {
//   bool leftValue = ir_left.isLine();
//   bool rightValue = ir_right.isLine();
//   bool middleValue = ir_middle.isLine();

//   if(!leftValue && !rightValue && !middleValue) {
//     if (lineLostTime == 0) {
//       lineLostTime = millis(); // Start the timer when line is lost
//     } else if (millis() - lineLostTime > 2000) { // If line is lost for more than 2 seconds
//       Serial.println("Line lost for too long, switching to MAZE_SOLVING state.");
//       motor.stop(); // Stop the motors
//       lineLostTime = 0; // Reset the timer
//       currentState = MAZE_SOLVING; // Switch to maze solving state
//       Serial.print("Switching to state: ");
//       Serial.println(stateToString(currentState));
//       return;
//     }
//   }
//   if (middleValue) { // Assuming a threshold for line detection
//     motor.moveForward(200); // Move forward
//   } else if (leftValue) {
//     motor.turnLeft(200); // Turn left
//   } else if (rightValue) {
//     motor.turnRight(200); // Turn right
//   } else {
//     motor.stop(); // Stop if no line detected
//   }
//   delay(100);
// }
void handleObstacle(){
  motor.stop();
  delay(500);
  while(obs.readValue() == LOW){
    motor.turnRight(100);
    delay(1000);
  }
  obs_flag = false; // Reset the obstacle flag
}
void handleMazeSolving() {
  if(obs_flag && !object){
    handleObstacle();
  } else if (object) {
    motor.stop();
    currentState = RESCUE;
    Serial.print("Switching to state: ");
    Serial.println(stateToString(currentState));

    return;
  }
  else if(ir_middle.isLine() && ir_left.isLine() && ir_right.isLine()) {
    delay(1000);
    motor.stop(); // Move forward if all sensors detect the line
    currentState = COMPLETE; // Set state to COMPLETE when the maze is solved
    Serial.print("Switching to state: ");
    Serial.println(stateToString(currentState));

    return;
  }
  else{
    motor.moveForward(200);
  }
}
void handleRescue() {
  // Implement rescue logic here
  // For example, navigate to a specific point or perform a specific action
  Serial.println("Handling rescue operation...");
  // After completing the rescue, switch back to line following or maze solving
  currentState = MAZE_SOLVING; // Or MAZE_SOLVING based on your logic
  Serial.print("Switching to state: ");
  Serial.println(stateToString(currentState));
  return;
}

const char* stateToString(State state) {
  switch (state) {
    case LINE_FOLLOWING: return "LINE_FOLLOWING";
    case MAZE_SOLVING: return "MAZE_SOLVING";
    case RESCUE: return "RESCUE";
    case COMPLETE: return "COMPLETE";
    default: return "UNKNOWN";
  }
}

void setup() {
  Serial.begin(115200);
  motor.begin();
  ir_middle.begin();
  ir_left.begin();
  ir_right.begin();
  obs.begin();

  // Use FALLING to detect transition from HIGH to LOW (obstacle present)
  attachInterrupt(digitalPinToInterrupt(obstacle_pin), obstacleDetected, FALLING);
}

void loop() {
  if (obs_flag) {
    // Handle obstacle avoidance
    handleObstacle();
    return;
  }

  if (currentState == LINE_FOLLOWING) {
    handleLineFollowing();
  } 
  else if (currentState == MAZE_SOLVING) {
    handleMazeSolving();  // You’ll define this later
  }
  else if (currentState == RESCUE) {
    handleRescue(); // Handle rescue operations
  } 
  else if (currentState == COMPLETE) {
    Serial.println("Operation complete.");
    motor.stop(); // Stop the motors
    while (true); // Halt the program
  }
}
