# Design and Implementation of an Intelligent Obstacle Avoidance and Tracking Car based on Arduino UNO R3
> [!IMPORTANT]
> The `Design and Implementation of an Intelligent Obstacle Avoidance and Tracking Car based on Arduino UNO R3` project aims to build and implement a smart car capable of automatic obstacle avoidance and line tracking through sensors and modules. The car is designed using `Arduino UNO R3` as the core processor.

<div align="left">
  <img src="https://img.shields.io/badge/-Arduino-blue.svg">
  <img src="https://img.shields.io/badge/-UNO R3-green.svg">
  <img src="https://img.shields.io/badge/-Bluetooth-orange.svg">
  <img src="https://img.shields.io/badge/-PID-purple.svg">
  <img src="https://img.shields.io/badge/-HC--SR04-yellow.svg">
  <img src="https://img.shields.io/badge/-C++-red.svg">
</div>

## Project Overview

| Feature      | Description                                                                |
|--------------|----------------------------------------------------------------------------|
| `Basic Control`     | Users can control the car to move forward, backward, turn left, and right, and adjust speed through a Bluetooth application.      |
| `Obstacle Avoidance`     | The car detects obstacles using ultrasonic ranging module and `FC-51` infrared obstacle avoidance module and makes response decisions.    |
| `Line Tracking`   | The car steadily tracks on a designated black line using the `PID` tracking module.                         |

## Personal Contribution

> [!IMPORTANT]
> 1. `Prepare project modules`: Prepare `Arduino UNO R3`, `HM-10` Bluetooth module, `L298N` motor driver module, `PID` tracking module, `FC-51` infrared obstacle avoidance module, `SG90` servo module, `HC-SR04` ultrasonic ranging module, and breadboard power module.
> 2. `Understand the working principles of each module`: Master the control of `Arduino` pins and their communication with other modules.
> 3. `Draw circuit diagram`: Use `Fritzing` software to design module connection schematic and evaluate the feasibility of the scheme.
> 4. `Assemble according to the circuit diagram`: Perform actual wiring to ensure functionality while maintaining a neat layout.
> 5. `Coding`: Write the car control logic and obstacle avoidance core code using the `Arduino` development platform, adjusting direction based on tracking module data.
> 6. `Deploy code to Arduino board`: Deploy the compiled code to the development board via serial communication.
> 7. `Debugging and completion`: Conduct field tests until the requirements of the test environment are met.

## System Architecture
<div align="left">
  <img src="https://github.com/user-attachments/assets/aba354b4-98b7-465a-967d-72d918e678cd" height="400">
</div>

### Setup Steps
> [!NOTE]
> 1. Reasonably allocate `Arduino pins` according to hardware
> 2. Determine the placement position of each module
> 3. Install `12V DC motor`
> 4. Install `L298N drive module`
> 5. Install the `Servo and ultrasonic module`
> 6. Install `FC-51 infrared obstacle avoidance module` and `infrared obstacle avoidance module`
> 7. Install the `HM-10 Bluetooth module`
> 8. Install the `PID tracking module` 
<div align="left">
  <img src="https://github.com/user-attachments/assets/1873aaed-6bf0-46ff-85a6-03af2d93f773" >
  <img src="https://github.com/user-attachments/assets/d6e0e185-c989-47f9-983e-d78a9180372f" >
  <img src="https://github.com/user-attachments/assets/bbab2c90-b81d-4829-8203-665c57c1c1f0" >
  <img src="https://github.com/user-attachments/assets/f9402b27-b454-4b2a-bc45-abcbc14f8e3f" >
</div>


## Implementation Details
| Aspect           | Description                                                                |
|-----------------|----------------------------------------------------------------------------|
| `Basic Control`     | Implement the basic movement controls of the car forwards, backwards, left, and right, and adjust the speed through a mobile terminal.  |
| `Obstacle Avoidance`     | Use sensors to detect nearby obstacles and make decisions to avoid them based on feedback data.         |
| `Line Tracking`     | The car steadily tracks on a black line between 1-4cm wide.                                                   |

## Actual Effects
> [!NOTE]
> Below are screenshots from the line tracking and obstacle avoidance operations. If you are interested, you can watch the following videos:
> [Line Tracking Video](https://github.com/DarrylXzq/Arduino/blob/main/TrackingVideo.mp4)
> [Obstacle Avoidance Video](https://github.com/DarrylXzq/Arduino/blob/main/ObstacleAvoidanceVideo.mp4)
<div align="left">
  <img src="https://github.com/user-attachments/assets/8b6cc3d5-2ca0-49a2-80c5-c421be48034a" >
  <img src="https://github.com/user-attachments/assets/ff5f3b77-7562-4ead-a903-2fbe7da476dc" >
  <img src="https://github.com/user-attachments/assets/ba34bc65-df78-4854-80c6-b2a23cdec03e" >
</div>

## Usage Restrictions
> [!WARNING]
> 1. This project and its code may `not` be used for any form of `commercial sales or services`.
> 2. The project must `not` be used as or embedded in any `commercial product`.

## 😄 Acknowledgements

 - Thanks to family, supervisors, and friends for their help.👋👋👋
 - [github-readme-stats](https://github.com/anuraghazra/github-readme-stats/blob/master/readme.md)
 - [Awesome Readme Templates](https://awesomeopensource.com/project/elangosundar/awesome-README-templates)
 - [Awesome README](https://github.com/matiassingers/awesome-readme)
 - [How to write a Good readme](https://bulldogjob.com/news/449-how-to-write-a-good-readme-for-your-github-project)

## 👋 Feedback

If you have any feedback, please reach out to us at `xiangzq.darryl@gmail.com`
