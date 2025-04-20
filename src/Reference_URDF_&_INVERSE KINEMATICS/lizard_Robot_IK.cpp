// lizard_ik.cpp
#include "lizard_robot_IK.h"
#include <cmath>

namespace LizardIK {

// Convert biological constraints from header files
constexpr float ARM_HUMERUS = 0.045f; // 45mm in meters
constexpr float ARM_RADIUS = 0.060f;
constexpr float LEG_FEMUR = 0.055f;
constexpr float LEG_TIBIA = 0.065f;

// Joint limits in radians (converted from degrees)
constexpr float ARM_SHOULDER_PAN_MIN = -0.785f;  // -45°
constexpr float ARM_SHOULDER_PAN_MAX = 0.785f;
constexpr float ARM_ELBOW_MIN = 0.0f;
constexpr float ARM_ELBOW_MAX = 2.094f;         // 120°
constexpr float LEG_HIP_YAW_MIN = -0.524f;      // -30°
constexpr float LEG_HIP_YAW_MAX = 0.698f;       // 40°
constexpr float LEG_KNEE_MIN = 0.175f;          // 10°
constexpr float LEG_KNEE_MAX = 2.268f;          // 130°

// Arm IK solver for URDF joint structure
ArmSolution solveArmIK(const Eigen::Vector3f& target) {
    ArmSolution solution;
    solution.valid = false;

    // Shoulder pan calculation (Z-axis rotation)
    float planar = std::hypot(target.x(), target.y());
    solution.shoulder_pan = std::atan2(target.y(), target.x());
    
    // Apply shoulder pan constraints
    solution.shoulder_pan = std::clamp(solution.shoulder_pan, 
                                     ARM_SHOULDER_PAN_MIN, 
                                     ARM_SHOULDER_PAN_MAX);

    // Elbow calculation (Law of Cosines)
    float c = (std::pow(ARM_HUMERUS, 2) + std::pow(ARM_RADIUS, 2) - 
              std::pow(planar, 2)) / (2 * ARM_HUMERUS * ARM_RADIUS);
    c = std::clamp(c, -1.0f, 1.0f);  // Prevent NaN
    solution.elbow = std::acos(c);

    // Apply elbow constraints
    solution.elbow = std::clamp(solution.elbow, 
                              ARM_ELBOW_MIN, 
                              ARM_ELBOW_MAX);

    // Wrist pitch (Z-axis orientation)
    solution.wrist = std::atan2(target.z(), planar);
    
    solution.valid = true;
    return solution;
}

// Leg IK solver for URDF joint structure
LegSolution solveLegIK(const Eigen::Vector3f& target) {
    LegSolution solution;
    solution.valid = false;

    // Hip yaw calculation (Z-axis rotation)
    solution.hip_yaw = std::atan2(target.y(), target.x());
    solution.hip_yaw = std::clamp(solution.hip_yaw, 
                                LEG_HIP_YAW_MIN, 
                                LEG_HIP_YAW_MAX);

    // Project to sagittal plane
    float planar = std::hypot(target.x(), target.y());
    float vertical = std::hypot(planar, target.z());

    // Knee calculation (Law of Cosines)
    float c = (std::pow(LEG_FEMUR, 2) + std::pow(LEG_TIBIA, 2) - 
              std::pow(vertical, 2)) / (2 * LEG_FEMUR * LEG_TIBIA);
    c = std::clamp(c, -1.0f, 1.0f);
    solution.knee = std::acos(c);
    
    // Apply knee constraints
    solution.knee = std::clamp(solution.knee, 
                             LEG_KNEE_MIN, 
                             LEG_KNEE_MAX);

    // Hip pitch calculation
    solution.hip_pitch = std::atan2(target.z(), planar);
    
    // Ankle compensation
    solution.ankle = -solution.hip_pitch * 0.5f;  // Biological adaptation

    solution.valid = true;
    return solution;
}

} // namespace LizardIK
