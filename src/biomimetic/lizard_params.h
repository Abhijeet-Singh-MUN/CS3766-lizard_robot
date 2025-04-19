//lizard biological constraints
#pragma once
#include "src/biomimetic/lizard_ik.h"  // Correct directory name
#include <stdint.h>

namespace LizardBio {
// Forelimb (Arm) Parameters - Gecko reference
constexpr float ARM_HUMERUS = 45.0f;    // Shoulder-to-elbow (mm)
constexpr float ARM_RADIUS = 60.0f;     // Elbow-to-wrist
constexpr float ARM_METACARPAL = 30.0f; // Wrist-to-foot

// Hindlimb (Leg) Parameters - Longer femur
constexpr float LEG_FEMUR = 55.0f;      // Hip-to-knee
constexpr float LEG_TIBIA = 65.0f;      // Knee-to-ankle
constexpr float LEG_METATARSAL = 25.0f; // Ankle-to-toe

// Joint ROM Limits (Degrees)
constexpr int8_t ARM_HIP_MIN = -45, ARM_HIP_MAX = 45;
constexpr uint8_t ARM_ELBOW_MIN = 0, ARM_ELBOW_MAX = 120;

constexpr int8_t LEG_HIP_MIN = -30, LEG_HIP_MAX = 40; 
constexpr uint8_t LEG_KNEE_MIN = 10, LEG_KNEE_MAX = 130;

// Add hip pitch constraints for legs
constexpr int8_t LEG_HIP_PITCH_MIN = -45;
constexpr int8_t LEG_HIP_PITCH_MAX = 45;

// Gait timing parameters
constexpr uint8_t STANCE_HIND = 400;  // 4 in relative units
constexpr uint8_t STANCE_FORE = 300;  // 3
constexpr uint8_t SWING_HIND = 300;   // 3 
constexpr uint8_t SWING_FORE = 200;   // 2
}
