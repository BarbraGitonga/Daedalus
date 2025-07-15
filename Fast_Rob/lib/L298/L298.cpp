#include <Arduino.h>

#include "L298.h"

L298::L298(const L298Pins& pins) {
    // Initialize the pins
    in1 = pins.in1;
    in2 = pins.in2;
    enA = pins.enA;
    in3 = pins.in3;
    in4 = pins.in4;
    enB = pins.enB;
    // Set the pin modes to OUTPUT
}

void L298::begin() {
    // Set the pin modes
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enA, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enB, OUTPUT);
}

void L298::moveForward(uint8_t speed){
    // Set the direction and speed for motor A
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, speed);

    // Set the direction and speed for motor B
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, speed);
}

void L298::reverse(uint8_t speed){
    // Set the direction and speed for motor A
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, speed);

    // Set the direction and speed for motor B
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enB, speed);
}

void L298::turnRight(uint8_t speed){
    // Set the direction and speed for motor A
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA,speed);

    // Set the direction and speed for motor B
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enB, speed);
}

void L298::turnLeft(uint8_t speed){
    // Set the direction and speed for motor A
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(enA, speed);

    // Set the direction and speed for motor B
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, speed);
}

void L298::stop() {
    // Stop motor A
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(enA, 0);

    // Stop motor B
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enB, 0);
}