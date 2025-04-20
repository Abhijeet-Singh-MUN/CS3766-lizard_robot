// lizard_ik.h
#pragma once
#include <Eigen/Dense>

namespace LizardIK {

struct ArmSolution {
    float shoulder_pan;  // Joint1 in URDF
    float elbow;         // Joint2
    float wrist;         // Joint3
    bool valid;
};

struct LegSolution {
    float hip_yaw;       // Joint1 in URDF
    float hip_pitch;     // Joint2
    float knee;          // Joint3
    float ankle;         // Joint4
    bool valid;
};

ArmSolution solveArmIK(const Eigen::Vector3f& target);
LegSolution solveLegIK(const Eigen::Vector3f& target);

} // namespace LizardIK
