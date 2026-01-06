# Self-Balancing Car Control PCB
## Overview
This PCB serves as the central control board for a self-balancing car system. It integrates the microcontroller, motor driver interface, power supply, and peripheral connectors into a single compact board.

Main functions:
- STM32-based real-time control
- Dual motor control interface
- IMU sensing for balance estimation
- Wireless communication and display support
- On-board DC-DC power regulation


## Key Components & Interfaces

### Microcontroller
- stmf103c8t6
- Handles real-time control loops, sensor acquisition, and communication
- Interrupt-driven architecture for deterministic timing

### Power System
- 12 V input
- On-board DC-DC converter for regulated logic supply

### Motor Control
- External motor driver module interface
- Separate connectors for Motor 1 and Motor 2

### Sensors & Peripherals
- MPU6050 IMU
- Ultrasonic sensor
- OLED display
- JDY-31 Bluetooth module
- TB6612FNG Motor Driver

## Tools
- PCB Design: Altium Designer  
- Board Type: 2-layer PCB  


