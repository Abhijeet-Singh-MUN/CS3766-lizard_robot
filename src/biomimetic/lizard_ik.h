// inverse kinematics for lizard arms and legs
#pragma once
#include <math.h>
#include "src\biomimetic\lizard_params.h"
#include <Arduino.h> 
#define _USE_MATH_DEFINES

namespace LizardIK {
// Arm-specific triangulation (2DOF planar)
inline void armIK(float x, float y, float z, 
                float& shoulder, float& elbow, float& wrist) {
  using namespace LizardBio;
  
  float planar = sqrt(x*x + y*y);
  shoulder = atan2(y, x) * RAD_TO_DEG;
  shoulder = constrain(shoulder, ARM_HIP_MIN, ARM_HIP_MAX); // Added constraint
  // Law of cosines for elbow
  float c = (ARM_HUMERUS*ARM_HUMERUS + ARM_RADIUS*ARM_RADIUS 
           - planar*planar) / (2*ARM_HUMERUS*ARM_RADIUS);
  elbow = acos(c) * RAD_TO_DEG;
  elbow = constrain(elbow, ARM_ELBOW_MIN, ARM_ELBOW_MAX); // Added constraint

  wrist = atan2(z, planar) * RAD_TO_DEG;
  wrist = constrain(wrist, -30, 30); // Wrist ROM from biological specs
}

// Leg-specific 3D solver (hip yaw + planar)
inline void legIK(float x, float y, float z,
                float& hipYaw, float& hipPitch, float& knee) {
  using namespace LizardBio;
  
  // 1. Calculate hip yaw rotation
  hipYaw = atan2(y, x) * RAD_TO_DEG;
  hipYaw = constrain(hipYaw, LEG_HIP_MIN, LEG_HIP_MAX); // Constrained yaw
  // 2. Project to vertical plane
  float planar = sqrt(x*x + y*y);
  float vertical = sqrt(planar*planar + z*z);
  
  // 3. Apply planar IK in sagittal plane
  float c = (LEG_FEMUR*LEG_FEMUR + LEG_TIBIA*LEG_TIBIA 
           - vertical*vertical) / (2*LEG_FEMUR*LEG_TIBIA);
  knee = acos(c) * RAD_TO_DEG;
  knee = constrain(knee, LEG_KNEE_MIN, LEG_KNEE_MAX); // Constrained knee

  
  // 4. Hip pitch calculation
  hipPitch = atan2(z, planar) * RAD_TO_DEG;
  hipPitch = constrain(hipPitch, -45, 45); // Added pitch constraints
  // Incorporate metatarsal
  float footOrientation = atan2(z - LEG_METATARSAL, planar);

  
}

