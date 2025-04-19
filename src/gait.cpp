#include "src\biomemetic\lizard_ik.h"

void lizardGait() {

  static float phase[4] = {0, 0.25, 0.5, 0.75};
  constexpr float strideLength = 45.0f; // Humerus length

  for(uint8_t leg=0; leg<4; leg++) {
    bool isArm = (leg < 2);
    bool isHind = (leg >= 2);
    float cyclePhase = fmod(phase[leg], 1.0f);

    // Trajectory calculation
    float x, y, z;
    if((isHind && cyclePhase < 0.4f) || (!isHind && cyclePhase < 0.3f)) {
      // Stance phase
      float progress = isHind ? cyclePhase/0.4f : cyclePhase/0.3f;
      x = strideLength * (1 - 2*progress);
      y = isArm ? 50.0f : -50.0f;
      z = 0.0f;
    } else {
      // Swing phase
      float swingProgress = isHind ? (cyclePhase-0.4f)/0.6f : (cyclePhase-0.3f)/0.7f;
      x = strideLength * cos(swingProgress * M_PI);
      y = isArm ? 50.0f : -50.0f;
      z = 30.0f * sin(swingProgress * M_PI); // 30mm clearance
    }

    // Inverse Kinematics
    float joint1, joint2, joint3;
    if(isArm) {
      LizardIK::armIK(x, y, z, joint1, joint2, joint3);
      setJoint(leg, HIP, constrain(joint1, LizardBio::ARM_HIP_MIN, LizardBio::ARM_HIP_MAX));
      setJoint(leg, ELBOW, constrain(joint2, LizardBio::ARM_ELBOW_MIN, LizardBio::ARM_ELBOW_MAX));
    } else {
      LizardIK::legIK(x, y, z, joint1, joint2, joint3);
      setJoint(leg, HIP_YAW, constrain(joint1, LizardBio::LEG_HIP_MIN, LizardBio::LEG_HIP_MAX));
      setJoint(leg, KNEE, constrain(joint3, LizardBio::LEG_KNEE_MIN, LizardBio::LEG_KNEE_MAX));
    }

    phase[leg] += isHind ? 0.004f : 0.003f;
  }
}


