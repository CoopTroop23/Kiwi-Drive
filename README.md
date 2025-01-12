# Kiwi-Drive
## Overview
This project is from when I had some extra free time in the summer of 2023. It is a Kiwi drive, a omni-directional three wheeled robot. Since the robot is omni-directional, it has the capability of moving in three directions along a planar surface. The three independent wheels allow the robot to move in any direction, or any combination of directions, at once.

## Hardware
This robot was constructed using the following materials:
* 20mm v-slot extrusion
* 12v DC motors
* l298n motor drivers
* 3" omni wheels
* remote controller
* Arduino

## Software
The software for the this robot was written with C++ for arduino. The motoion of the robot was also simulated using matlab. The Matlab simulation computed algebraic formulas for the robot that were then implemented in C++. The code used a desired translation and rotation velocity as an input and used inverse kinematics to find what velocity each wheel should spin at to achive the operation. 

## future updates
In the future, I would like to add closed loop feedback to this project to have more accurate motion. The robot had a lot of drift from translational motion. This was fine since it was driver controlled. However, if a more autonomous version is required, sensors will be needed.
