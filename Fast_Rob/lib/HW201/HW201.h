/**
 * @file HW201.h
 * @author Barbra Gitonga (barbragitonga@gmail.com)
 * @brief This is a header file for the HW201 class for the HW201 IR sensor.
 * @version 0.1
 * @date 2025-07-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef HW201_H
#define HW201_H

#include <Arduino.h>
class HW201 {
public:
    HW201(uint8_t pin);
    void begin();
    bool isLine();
private:
    uint8_t _pin;
};

#endif // HW201_H