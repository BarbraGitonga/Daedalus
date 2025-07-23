#include "IR08H.h"

IR08H::IR08H(uint8_t pin) : _pin(pin) {
    // Constructor implementation
}

void IR08H::begin() {
    pinMode(_pin, INPUT);  // Set the pin mode to INPUT
}

int IR08H::readValue() {                       // Allow pulse and signal to stabilize (1ms)
      
    return digitalRead(_pin);  // Read the value from the sensor
}