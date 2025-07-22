#ifndef IR08H_H
#define IR08H_H

#include <Arduino.h>

class IR08H {
public:
    /**
     * @brief Construct a new IR08H object.
     * 
     * @param pin The pin number to which the IR08H sensor is connected.
     */
    IR08H(uint8_t out, uint8_t EN);

    /**
     * @brief Initialize the IR08H sensor.
     */
    void begin();

    /**
     * @brief Read the value from the IR08H sensor.
     * 
     * @return int The value read from the sensor.
     */
    int readValue();
private:
    uint8_t _pin;  // Pin number for the IR08H sensor
    uint8_t _EN;   // Enable pin for the IR08H sensor (if applicable)
};

#endif // IR08H_H