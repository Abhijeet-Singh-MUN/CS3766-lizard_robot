#include "biomimetic/lizard_ik.h"

void lizardGait() {
  for(int leg=0; leg<4; leg++) {
    bool isArm = (leg < 2); // Front legs as arms
    
    float x,y,z; // Trajectory calculation
    // ... existing foot path logic
    
    float joint1, joint2, joint3;
    if(isArm) {
      LizardIK::armIK(x, y, z, joint1, joint2, joint3);
      setJoint(leg, HIP, constrain(joint1, 
               LizardBio::ARM_HIP_MIN, LizardBio::ARM_HIP_MAX));
      setJoint(leg, ELBOW, constrain(joint2, 
               LizardBio::ARM_ELBOW_MIN, LizardBio::ARM_ELBOW_MAX));
    } else {
      LizardIK::legIK(x, y, z, joint1, joint2, joint3);
      setJoint(leg, HIP_YAW, constrain(joint1, 
               LizardBio::LEG_HIP_MIN, LizardBio::LEG_HIP_MAX));
      setJoint(leg, KNEE, constrain(joint3, 
               LizardBio::LEG_KNEE_MIN, LizardBio::LEG_KNEE_MAX));
    }
  }
}
