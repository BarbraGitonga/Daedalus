/**
 * @file HW201.cpp
 * @author Barbra Gitonga (barbragitonga@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "HW201.h"

HW201::HW201(uint8_t pin) : _pin(pin) {
    // Constructor implementation
}

/**
 * @brief sets the pin mode for the HW201 IR sensor.
 * 
 */
void HW201::begin() {
    pinMode(_pin, INPUT);  // Set the pin mode to INPUT
}

/**
 * @brief Reads the value from the HW201 IR sensor.
 * This sensor is active low, meaning it outputs LOW when an obstacle is detected.
 * 
 * @return int 
 */
int HW201::readValue() {
    // Read the analog value from the sensor pin
    return digitalRead(_pin);  // Read the value from the sensor
}