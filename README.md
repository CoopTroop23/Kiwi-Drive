# Kiwi-Drive
## Overview
This project is from when I had some extra free time in the summer of 2023. It is a Kiwi drive, a omni-directional three wheeled robot. Since the robot is omni-directional, it has the capability of moving in three directions along a planar surface. The three independent wheels allow the robot to move in any direction, or any combination of directions, at once.

## Hardware
This robot was constructed using the following materials:
* 20mm v-slot extrusion
* 12v DC motors
* l298n motor drivers
* 3" omni wheels
* remote controller and reciever
* Arduino

## Software
The software for the this robot was written with C++ for arduino. The motoion of the robot was also simulated using matlab. The Matlab simulation computed algebraic formulas for the robot that were then implemented in C++. The code used a desired translation and rotation velocity as an input and used inverse kinematics to find what velocity each wheel should spin at to achive the operation. 
### How this janky code works
The remote controller sends a signal to the reciever. The reciever then outputs a PPM signal that the arduino picks up on. Based on this signal, which corelates to the position of the controller sticks, the velocity of each wheel is calculated (from the formulas of the Matlab code). The motors are then told to run at that speed and the process repeats.

## CAD
All of the liminal cad files can be found on my [Tinkecad](https://www.tinkercad.com/things/kuo86JpVjGv-triangular-omni-robot) page. It has the 3D printed gussets I used with the project and you can download them for free.

## Future Updates
In the future, I would like to add closed loop feedback to this project to have more accurate motion. The robot had a lot of drift from translational motion. This was fine since it was driver controlled. However, if a more autonomous version is required, sensors will be needed. That being said, I am not sure if I will revisit this topic because I would like to pursue other ideas.
