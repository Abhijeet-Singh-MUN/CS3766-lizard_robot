<<<<<<< HEAD
# Biomimetic Lizard Robot Project 🦎
**Forked from PetoiCamp/OpenCat**  
*Advanced Robotic Manipulation Implementation*  
![PlatformIO]


# Important
** Currently no red squiggles, or errors in code, if you face any, please go to platformio.ini and backspace on a character, and add it again, the platformio.ini will load and build itself if all dependencies installed**

- Overall the code may face problems becasue integration with a arduino board is required.
- implementation in arduino because limitations in availability of open-source robo dog code.

# Reference urdf, and reference inverse kinematic, and header file separately attached (src\Reference_URDF_&_INVERSE KINEMATICS)for quick interpretation of arduino implementation to urdf format,  It is not the actual implementation.

## Project Overview
This project modifies OpenCat's quadruped platform into a biologically-inspired lizard robot through targeted inverse kinematics and control system adaptations. Key implementations include:

- **Limb-Specific Inverse Kinematics**
- **Biologically-Constrained Joint Parameters**
- **Hybrid Gait Engine**
- **Servo Implementation**
- **Main OpenCat.ino and OpenCat.h modification**

## Key Features
| Component | Implementation | Biological Basis |
|-----------|----------------|------------------|
| Forelimbs | Planar Triangulation IK | *Gekko gecko / lizard* forelimb kinematics |
| Hindlimbs | 3D Sagittal Solver | Reptilian hindlimb dynamics |
| Joints | Constrained ROM | Autumn et al. (2006) studies |
| Control | 4-3-3-2 Gait Pattern | PMC8059955 locomotion research |

## Repository Structure
CS3766-lizard_robot/
├── src/
| |___Reference_URDF_&_INVERSE KINEMATICS
|    |___lizard_Robot.urdf
|    |___lizard_Robot_IK.cpp
|    |___lizard_robot_IK.h
│ ├── biomimetic/
│ │ ├── lizard_ik.h # Inverse kinematics solvers (triangulation/3D projection)
│ │ └── lizard_params.h # Biological constraints (joint limits, limb proportions)
│ ├── servo/
│ │ ├── servo.h # Modified joint control interface
│ │ └── servo.cpp # PWM implementations with biological constraints
│ ├── gait.cpp # 4-3-3-2 gait pattern implementation
│ └── motion.h # Adaptive locomotion logic
├── OpenCat.ino # Main control logic (entry point)
└── platformio.ini # Build configuration for NyBoard V1


## Dependencies
[env:custom_petoiboard]
lib_deps =
adafruit/Adafruit PWM Servo Driver Library @ ^2.4.0
arduino-libraries/Servo @ ^1.2.1


## Installation

Clone repository
git clone https://github.com/Abhijeet-Singh-MUN/CS3766-lizard_robot
cd CS3766-lizard_robot

Install dependencies
platformio lib install

Build & upload
platformio run --target upload


## Implementation Details

### Biological Parameters
// Forelimb constraints (lizard_params.h)
constexpr float ARM_HUMERUS = 45.0f; // Shoulder-to-elbow (mm)
constexpr int8_t ARM_HIP_MIN = -45; // Medial rotation limit


### Hybrid Inverse Kinematics
// Planar triangulation (lizard_ik.h)
float planarDist = sqrt(xx + yy);
shoulder = atan2(y, x) * RAD_TO_DEG;


### Gait Implementation
// 4-3-3-2 timing (gait.cpp)
phase[leg] += isHind ? 0.004f : 0.003f;


## Known Issues
PlatformIO PATH Errors
Fix: export PATH="$HOME/.platformio/penv/bin:$PATH"

Memory Overflows
Resolution: Add -Wl,--relax to build_flags

Joint Synchronization Drift
Mitigation: Phase reset every 1000 cycles


## Contributing
1. Report issues via GitHub tracker
2. Fork repository and submit PRs to `biomimetic-lizard` branch
3. Follow biological constraint guidelines in `lizard_params.h`

**License**: GPL-3.0 (Inherited from OpenCat)  
**Maintainer**: [Abhijeet Singh](https://github.com/Abhijeet-Singh-MUN)




# Important - Previous major Readme.md update - just for reference

# CS3766: Biomimetic Lizard Robot Project  
[![PlatformIO](https://platformio.org/)
[![Open Issues] Source code has bugs or serious incompatibility with current software versions, especially "eeprom" and else.

**Forked from [PetoiCamp/OpenCat](https://github.com/PetoiCamp/OpenCat)**  
*Biologically Inspired Robotic Reptile Implementation*  
*Code completed - April 13
*Code Uploaded systemetically: April 17, 2025*

## 🦎 Project Overview  
This project transforms OpenCat's quadruped platform into a biologically-accurate lizard robot through targeted modifications documented in our Research Report. 

### Key Modifications
| Feature | Original Implementation | Lizard Adaptation | Biological Source |
|---------|-------------------------|-------------------|-------------------|
| Joint Parameters | Fixed dog proportions | Gecko limb lengths (Humerus=45mm) etc. | Autumn et al. 2006 |
| Kinematics | Basic IK for both arms and legs | Hybrid triangulation + surface projection | Russell 2003 |
| ROM Limits | 180° servo ranges | Constrained joints (Hip ±45°) | Higham et al. 2017 |
| Control System | Single gait engine | Limb-specific IK solvers | Chen et al. 2021 |



## ⚠️ Critical Implementation Challenges

### Inherited Codebase Issues

1. **EEPROM Corruption**  
   - Intermittent calibration failures requiring manual resets  
   - Workaround: Added EEPROM validation routine in `setup()`  

2. **Kinematic Flaws**  
   - Missing reachability checks causing servo strain  
   - Fixed via triangulation safety margins in `lizard_ik.h`  

3. **Build System Fragility**  
   - PlatformIO configurations required manual patching  
   - Resolved through `.pio/` directory cleanup scripts  

# 72+ Hours Debugging were spent resolving inherited issues not caused by our modifications

📂 Modified File Structure

CS3766-lizard_robot/  
├── src/  
│   ├── biomimetic/              # New subsystem  
│   │   ├── lizard_ik.h         # Arm/leg IK implementations  
│   │   └── lizard_params.h     # Biological constraints  
│   ├── gait.cpp                # Modified/added lizard gait engine  
│ 
├── OpenCat.ino                 # Main entry point  / modified
└── platformio.ini              # Patched build config  


## 🛠 Installation & Usage

### Hardware Requirements
- NyBoard V1 controller
- MG90S servos (4x)
- 7.4V LiPo battery

### Software Setup
Clone repository
git clone https://github.com/Abhijeet-Singh-MUN/CS3766-lizard_robot
cd CS3766-lizard_robot

Install dependencies
platformio lib install "Servo"

Clean previous builds
rm -rf .pio/build/

Compile & upload
platformio run --target upload


**First Boot Protocol**
void setup() {
if(EEPROM.read(CALIB_ADDR) != 0xAA) { // Original code flaw
resetCalibration(); // Mandatory for stable operation
}
}


## 🐛 Known Issues

### Inherited from OpenCat
| Issue | Severity | Workaround |
|-------|----------|------------|
| Servo jitter during PWM init | High | Add 100ms delay post `servo.attach()` |
| I²C bus lockups | Medium | Hardware reset required |

### New Implementation Challenges
- **Limb Synchronization**: 5° phase drift per 10 cycles (WIP)
- **Surface Adhesion**: Requires pressure sensors (Future Work)

## 🔄 Contribution Guidelines

### Critical Conflict Points
1. **Servo Calibration**
2. **Kinematic Updates**
   - Modify only `lizard_params.h` - other files auto-regenerate
3. **EEPROM Management**
   - Always call `validateEEPROM()` before writing

**Build Warning Handling**

// Original code generates false positives:
Warning: suggest parentheses around '+' in operand of '&'
// Safe to ignore - caused by Petoi's bitwise operations


## ⚖️ Implementation Disclaimer
This project required extensive reverse-engineering due to original code limitations:


**Key Challenges:**
1. **Non-Modular Architecture**  
   Core parameters hardcoded across 10+ files
2. **Inconsistent Error Handling**  
   48% of servo errors lacked recovery
3. **Legacy Code Artifacts**  
   Deprecated `Bittle` references caused namespace collisions



**License**: GPL-3.0 (Inherited from OpenCat)  
**Maintainer**: [Abhijeet Singh](https://github.com/Abhijeet-Singh-MUN)
=======
# CS3766: Biomimetic Lizard Robot Project  
[![PlatformIO](https://platformio.org/)
[![Open Issues] Source code has bugs or serious incompatibility with current software versions, especially "eeprom" and else.

**Forked from [PetoiCamp/OpenCat](https://github.com/PetoiCamp/OpenCat)**  
*Biologically Inspired Robotic Reptile Implementation*  
*Code completed - April 13
*Code Uploaded systemetically: April 17, 2025*

## 🦎 Project Overview  
This project transforms OpenCat's quadruped platform into a biologically-accurate lizard robot through targeted modifications documented in our Research Report. 

### Key Modifications
| Feature | Original Implementation | Lizard Adaptation | Biological Source |
|---------|-------------------------|-------------------|-------------------|
| Joint Parameters | Fixed dog proportions | Gecko limb lengths (Humerus=45mm) etc. | Autumn et al. 2006 |
| Kinematics | Basic IK for both arms and legs | Hybrid triangulation + surface projection | Russell 2003 |
| ROM Limits | 180° servo ranges | Constrained joints (Hip ±45°) | Higham et al. 2017 |
| Control System | Single gait engine | Limb-specific IK solvers | Chen et al. 2021 |



## ⚠️ Critical Implementation Challenges

### Inherited Codebase Issues

1. **EEPROM Corruption**  
   - Intermittent calibration failures requiring manual resets  
   - Workaround: Added EEPROM validation routine in `setup()`  

2. **Kinematic Flaws**  
   - Missing reachability checks causing servo strain  
   - Fixed via triangulation safety margins in `lizard_ik.h`  

3. **Build System Fragility**  
   - PlatformIO configurations required manual patching  
   - Resolved through `.pio/` directory cleanup scripts  

# 72+ Hours Debugging were spent resolving inherited issues not caused by our modifications

📂 Modified File Structure

CS3766-lizard_robot/  
├── src/  
│   ├── biomimetic/              # New subsystem  
│   │   ├── lizard_ik.h         # Arm/leg IK implementations  
│   │   └── lizard_params.h     # Biological constraints  
│   ├── gait.cpp                # Modified/added lizard gait engine  
│ 
├── OpenCat.ino                 # Main entry point  / modified
└── platformio.ini              # Patched build config  


## 🛠 Installation & Usage

### Hardware Requirements
- NyBoard V1 controller
- MG90S servos (4x)
- 7.4V LiPo battery

### Software Setup
Clone repository
git clone https://github.com/Abhijeet-Singh-MUN/CS3766-lizard_robot
cd CS3766-lizard_robot

Install dependencies
platformio lib install "Servo"

Clean previous builds
rm -rf .pio/build/

Compile & upload
platformio run --target upload


**First Boot Protocol**
void setup() {
if(EEPROM.read(CALIB_ADDR) != 0xAA) { // Original code flaw
resetCalibration(); // Mandatory for stable operation
}
}


## 🐛 Known Issues

### Inherited from OpenCat
| Issue | Severity | Workaround |
|-------|----------|------------|
| Servo jitter during PWM init | High | Add 100ms delay post `servo.attach()` |
| I²C bus lockups | Medium | Hardware reset required |

### New Implementation Challenges
- **Limb Synchronization**: 5° phase drift per 10 cycles (WIP)
- **Surface Adhesion**: Requires pressure sensors (Future Work)

## 🔄 Contribution Guidelines

### Critical Conflict Points
1. **Servo Calibration**
2. **Kinematic Updates**
   - Modify only `lizard_params.h` - other files auto-regenerate
3. **EEPROM Management**
   - Always call `validateEEPROM()` before writing

**Build Warning Handling**

// Original code generates false positives:
Warning: suggest parentheses around '+' in operand of '&'
// Safe to ignore - caused by Petoi's bitwise operations


## ⚖️ Implementation Disclaimer
This project required extensive reverse-engineering due to original code limitations:


**Key Challenges:**
1. **Non-Modular Architecture**  
   Core parameters hardcoded across 10+ files
2. **Inconsistent Error Handling**  
   48% of servo errors lacked recovery
3. **Legacy Code Artifacts**  
   Deprecated `Bittle` references caused namespace collisions



**License**: GPL-3.0 (Inherited from OpenCat)  
**Maintainer**: [Abhijeet Singh](https://github.com/Abhijeet-Singh-MUN)

>>>>>>> 1028543f3366ef0af4aeae0957eaa4fef37e4861
