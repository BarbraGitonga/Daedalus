#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
// H201 IR sensor configurations
#define ir1_pin 10  // Pin for the first HW201 IR sensor
#define ir2_pin 11  // Pin for the second HW201 IR sensor

// IR08H sensor configurations
#define ir_middle_pin 6  // Pin for the middle IR08H sensor
#define ir_middle_enable_pin 9  // Enable pin for the middle IR08H sensor
// L298 motor driver configurations
#define in1 2  // Pin for IN1 control
#define in2 3  // Pin for IN2 control
#define enA 0  // Pin for ENA control
#define in3 4  // Pin for IN3 control
#define in4 5  // Pin for IN4 control
#define enB 1  // Pin for ENB control

#endif // CONFIG_H