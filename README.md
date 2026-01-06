# balance-car-stm32

Self-balancing robot built on **STM32F103 (Blue Pill)** with **MPU6050 IMU** and real-time control.  
This repository includes firmware (`src/`) and custom control PCB design assets (`pcb/`).

> Keywords: STM32F103C8T6, MPU6050, PID control, timers/interrupts, motor driver, Bluetooth (JDY-31), OLED, ultrasonic sensor

---

## showcase
-  [`images/`](images) / [`pcb/`](pcb) 

---

## What I Built
- **Real-time control firmware** on STM32 (interrupt/timer driven)
- **Nested PID control** for balancing (and optional velocity loop / remote control input)
- **IMU interface** (MPU6050 over I²C) for tilt estimation
- **Peripheral interfaces** for OLED display, Bluetooth module (JDY-31), and ultrasonic sensor
- **Custom control PCB** integrating MCU, power regulation, and connectors

---

## Hardware Overview
Typical setup for this project:
- MCU: **STM32F103C8T6 (Blue Pill form factor)**
- IMU: **MPU6050**
- Motor driver module + two DC motors
- Optional peripherals: OLED, JDY-31 Bluetooth, ultrasonic sensor
- Power input: **12 V** (regulated on-board via DC-DC)

---

## PCB (Custom Control Board)
The PCB integrates power input, DC-DC regulation, STM32 header footprint, and connectors for sensors and peripherals.

![PCB Layout](images/pcb_overall.png)

If you want the PCB-specific README, see: [`pcb/`](pcb)

### Hall Encoder Wiring (if applicable)
1. Motor −  
2. Encoder Power (VCC)  
3. Encoder Output A (Channel A)  
4. Encoder Output B (Channel B)  
5. Encoder Ground (GND)  
6. Motor +  

---

## Repository Structure
```text
balance-car-stm32/
├─ src/                Firmware source code
├─ pcb/                PCB design notes/assets (screenshots, PDFs, etc.)
├─ images/             Images used by README (PCB/layout/photos)
├─ Balanced Car.uvprojx  Keil uVision project file
├─ .gitignore
└─ .clang-format
