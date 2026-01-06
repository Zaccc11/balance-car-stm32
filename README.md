# balance-car-stm32

Self-balancing robot built on **STM32F103 (Blue Pill)** with **MPU6050 IMU** and real-time control.  
This repository includes firmware (`src/`) and custom control PCB design assets (`pcb/`).

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
- MCU: **STM32F103C8T6 **
- IMU: **MPU6050**
- TB6612FNG Motor driver module + two MG513P30 hall encoder dc motor
- 0.96-inch OLED display, JDY-31 Bluetooth module, hc-sr04 ultrasonic sensor
- Power input: **12 V** (regulated on-board via DC-DC)

---

## PCB
The PCB integrates power input, DC-DC regulation, STM32 header footprint, and connectors for sensors and peripherals.

![PCB Layout](pcb/3D_pcb)

If you want the PCB-specific README, see: [`pcb/`](pcb)

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
