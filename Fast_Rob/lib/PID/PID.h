/**
 * @file PID.h
 * @author Barbra Gitonga (barbragitonga@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-07-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef PID_H
#define PID_H
class PID {
    public: 
        PID(double kp, double ki, double kd, int *weights, int sensor_number);
        double compute(int *sensors);
        void reset();
    private:
        double kp; // Proportional gain
        double ki; // Integral gain
        double kd; // Derivative gain
        int *weights; // Array of weights for PID components
        double target; // Desired target value
        int sensors; // Length of the weights array
        double previous_error; // Previous error for derivative calculation
        double previous_value;
        int sensor_number; // Number of sensors
        double error;
        double integral; // Integral of the error
        double derivative; // Derivative of the error
        double position; // Current position based on sensor readings
};

#endif // PID_H