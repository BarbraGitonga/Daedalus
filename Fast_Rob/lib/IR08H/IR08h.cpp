#include "IR08H.h"

IR08H::IR08H(uint8_t pin, uint8_t EN) : _pin(pin), _EN(EN) {
    // Constructor implementation
}

void IR08H::begin() {
    pinMode(_pin, INPUT);  // Set the pin mode to INPUT
    pinMode(_EN, OUTPUT);  // Set the enable pin mode to OUTPUT if applicable
}

int IR08H::readValue() {
    digitalWrite(_EN,LOW);  // Disable the sensor if applicable
    digitalWrite(_EN,HIGH); // Enable the sensor if applicable
    delay(2);
    digitalWrite(_EN,LOW);  // Disable the sensor again
  // Read the analog value from the sensor pin
    return digitalRead(_pin);  // Read the value from the sensor
}