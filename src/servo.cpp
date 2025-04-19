#include "servo.h"
#include "config.h" // OpenCat's config

void setJoint(uint8_t leg, uint8_t joint, float angle) {
  // Convert angle to pulse using OpenCat's existing logic:
  int pulse = angle * 11.11 + 500; // From OpenCat's servoCalib[]
  pulse = constrain(pulse, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  
  // Use modified Servo class
  servos[leg][joint].writeMicroseconds(pulse);
}
