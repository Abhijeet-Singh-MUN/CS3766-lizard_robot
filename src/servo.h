# pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

extern Adafruit_PWMServoDriver pwm; // Declare extern

class Servo {
private:
  uint8_t _pin;
  float _offset;
  bool _dir;
  uint8_t _jointType;
  
public:
  void init(uint8_t pin, float offset, bool dir, uint8_t jointType);
  void writeMicroseconds(uint16_t pulse);
  void init(int pin, float offset, bool dir, uint8_t jointType) {
    _pin = pin;
    _offset = offset;
    _dir = dir;
    if(jointType == SPHERICAL) 
      setSpeed(SPEED_MIN); // From OpenCat's constants
  }

  void writeMicroseconds(int pulse) {
    // Use OpenCat's existing PCA9685 driver
    pwm.setPWM(_pin, 0, pulse); 
  }
};