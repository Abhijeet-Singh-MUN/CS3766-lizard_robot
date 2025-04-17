// inverse kinematics for lizard arms and legs
#pragma once
#include <math.h>
#include "lizard_params.h"

namespace LizardIK {
// Arm-specific triangulation (2DOF planar)
inline void armIK(float x, float y, float z, 
                float& shoulder, float& elbow, float& wrist) {
  using namespace LizardBio;
  
  float planar = sqrt(x*x + y*y);
  shoulder = atan2(y, x) * RAD_TO_DEG;
  
  // Law of cosines for elbow
  float c = (ARM_HUMERUS*ARM_HUMERUS + ARM_RADIUS*ARM_RADIUS 
           - planar*planar) / (2*ARM_HUMERUS*ARM_RADIUS);
  elbow = acos(c) * RAD_TO_DEG;
  
  wrist = atan2(z, planar) * RAD_TO_DEG;
}

// Leg-specific 3D solver (hip yaw + planar)
inline void legIK(float x, float y, float z,
                float& hipYaw, float& hipPitch, float& knee) {
  using namespace LizardBio;
  
  // 1. Calculate hip yaw rotation
  hipYaw = atan2(y, x) * RAD_TO_DEG;
  
  // 2. Project to vertical plane
  float planar = sqrt(x*x + y*y);
  float vertical = sqrt(planar*planar + z*z);
  
  // 3. Apply planar IK in sagittal plane
  float c = (LEG_FEMUR*LEG_FEMUR + LEG_TIBIA*LEG_TIBIA 
           - vertical*vertical) / (2*LEG_FEMUR*LEG_TIBIA);
  knee = acos(c) * RAD_TO_DEG;
  
  // 4. Hip pitch calculation
  hipPitch = atan2(z, planar) * RAD_TO_DEG;
}
}
