/**
 * @file L298.h
 * @author Barbra Gitonga (barbragitonga@gmail.com)
 * @brief a header file for the L298 motor driver library
 * @version 0.1
 * @date 2025-07-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef L298_H
#define L298_H
#include <Arduino.h>
#include <stdint.h>


typedef struct L298Pins {
    uint8_t in1;  // Pin for IN1 control
    uint8_t in2;  // Pin for IN2 control
    uint8_t enA;  // Pin for ENA control
    uint8_t in3;  // Pin for IN3 control
    uint8_t in4;  // Pin for IN4 control
    uint8_t enB;  // Pin for ENB control
};
/**
 * @brief Class for controlling the L298 motor driver.
 */
class L298 {
public:
    /**
     * @brief Construct a new L298 object.
     * 
     * @param in1 Pin for IN1 control.
     * @param in2 Pin for IN2 control.
     * @param enA Pin for ENA control.
     * @param in3 Pin for IN3 control.
     * @param in4 Pin for IN4 control.
     * @param enB Pin for ENB control.
     */
    L298(const L298Pins& pins);

    /**
     * @brief Initialize the motor driver pins.
     */
    void begin();

    /**
     * @brief Move the motors forward.
     * 
     * @param speed Speed value (0-255).
     */
    void moveForward(uint8_t speed);

    /**
     * @brief Move the motors backward.
     * 
     * @param speed 
     */
    void reverse(uint8_t speed);

    /**
     * @brief Set the speed of motor A.
     * 
     * @param speed Speed value (0-255).
     */
    void turnRight(uint8_t speed);

    /**
     * @brief Set the speed of motor B.
     * 
     * @param speed Speed value (0-255).
     */
    void turnLeft(uint8_t speed);

    /**
     * @brief Stop both motors.
     */
    void stop();
private:
    uint8_t in1;
    uint8_t in2;
    uint8_t enA;
    uint8_t in3;
    uint8_t in4;
    uint8_t enB;  
};

#endif // L298_H