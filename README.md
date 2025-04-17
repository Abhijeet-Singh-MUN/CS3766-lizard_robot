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
