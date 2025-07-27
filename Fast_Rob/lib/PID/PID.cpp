/**
 * @file PID.cpp
 * @author Barbra Gitonga (barbragitonga@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "PID.h"
#include "Arduino.h"
#include <cmath>
PID::PID(double kp, double ki, double kd, int* weights, int sensor_number)
    : kp(kp), ki(ki), kd(kd), weights(weights), sensor_number(sensor_number) {
    this->target = 0;
    this->previous_value = 0;
    this->previous_error = 0;
    this->error = 0;
    this->integral = 0;
    this->derivative = 0;
    this->position = 0;
}

void PID::reset() {
    this->target = 0;
    this->previous_value = 0;
    this->previous_error = 0;
    this->error = 0;
    this->integral = 0;
    this->derivative = 0;
    this->position = 0;
}
double PID::compute(int *sensors) {
    int sum = 0, count = 0;
    // Computing weighted sum of PID components
    for (int i = 0; i < this->sensor_number; i++){
        if (sensors[i] == true){
            sum += this->weights[i];
            count++;
        }
    }

    // Calculating the current position based on the weighted sum
    this->position = (float)sum / count;

    // Calculating the error (proportional term)
    error = this->target - this->position;
    // Integral term calculation
    integral += error;
    // Derivative term calculation
    derivative = error - previous_error;
    // Correction
    double correction = (kp * error) + (ki * integral) + (kd * derivative);

    this->previous_error = error;
    this->previous_value = position;
    
    return correction;
}
