# Rocket CanSat 2025

A modular telemetry and environmental-monitoring payload for educational rockets and CanSat/CubeSat prototypes. The repository preserves the complete V1 development history: onboard firmware, a ground receiver, test sketches, wiring, logs and presentation materials.

<p align="center">
  <img src="images/V-1/real-photos/V-1-5.jpeg" alt="Assembled Rocket CanSat V1 prototype" width="46%">
  <img src="images/V-1/pcb-renders/black-1.PNG" alt="Rocket CanSat V1 PCB render" width="46%">
</p>

<p align="center">
  <a href="README-RU.md">Русская версия</a> ·
  <a href="https://www.youtube.com/watch?v=PDBPk4lwok4">Launch video</a> ·
  <a href="V-1.x/V-1.2/cansat_v1.2_master/cansat_v1.2_master.ino">V1.2 master</a> ·
  <a href="V-1.x/V-1.2/cansat_v1.2_slave/cansat_v1.2_slave.ino">V1.2 logger</a>
</p>

## Achievement

An early version of this system won **2nd place at the 2023 Eurasian Rocketry Challenge**, held at Satbayev University in Kazakhstan.

## System overview

| Subsystem | V1 implementation |
| --- | --- |
| Main controller | Arduino-compatible master controller |
| Motion sensing | MPU6050 accelerometer and gyroscope |
| Atmosphere | BMP280 temperature, pressure and barometric altitude |
| Gas experiments | MQ-2, MQ-8 and MQ-135 |
| Radio telemetry | nRF24L01, 2.4 GHz |
| Logging | Secondary controller with microSD storage |
| Video | Independent 5.8 GHz FPV link |

### Data path

1. The **master** reads the inertial, barometric and gas sensors.
2. It sends a telemetry structure over nRF24 and forwards the same data to the secondary controller over a serial link.
3. The **slave/logger** writes received measurements to `datalog.txt` on a microSD card.
4. The **ground receiver** displays radio telemetry through the Serial Monitor.

The V1.2 firmware integrates BMP280, MPU6050, MQ-2, MQ-8, MQ-135, nRF24 and microSD logging. Additional folders preserve experiments with a radiation detector, DHT11 and individual communication stages; these are development tests rather than one fully integrated release.

## Versions

| Version | Master | Logger / slave | Ground receiver |
| --- | --- | --- | --- |
| V1.0 | [Open](V-1.x/V-1.0/cansat_v1.0_master/cansat_v1.0_master.ino) | [Open](V-1.x/V-1.0/cansat_v1.0_slave/cansat_v1.0_slave.ino) | — |
| V1.1 | [Open](V-1.x/V-1.1/cansat_v1.1_master/cansat_v1.1_master.ino) | [Open](V-1.x/V-1.1/cansat_v1.1_slave/cansat_v1.1_slave.ino) | [Open](V-1.x/V-1.1/receiver/receiver.ino) |
| V1.2 | [Open](V-1.x/V-1.2/cansat_v1.2_master/cansat_v1.2_master.ino) | [Open](V-1.x/V-1.2/cansat_v1.2_slave/cansat_v1.2_slave.ino) | Uses the compatible V1 receiver concept |

## Documentation and media

- [Complete wiring diagram](docs/wiring/V-1/wiring.PNG)
- [PCB layout diagram](docs/wiring/V-1/pcb-board.PNG)
- [Example telemetry log](docs/logs/DATALOG.txt)
- [Project presentation — PDF](docs/showcase/Cansat.pdf)
- [Project presentation — PowerPoint](docs/showcase/Cansat.pptx)
- [Archived demonstration video](docs/showcase/WhatsApp%20Video%202024-09-27%20at%2011.02.48.mp4)
- [PCB renders](images/V-1/pcb-renders)
- [Prototype photographs](images/V-1/real-photos)
- [Launch video on YouTube](https://www.youtube.com/watch?v=PDBPk4lwok4)

## Repository map

| Path | Contents |
| --- | --- |
| [`V-1.x/V-1.0`](V-1.x/V-1.0) | First integrated prototype |
| [`V-1.x/V-1.1`](V-1.x/V-1.1) | Updated sensors, logging and ground receiver |
| [`V-1.x/V-1.2`](V-1.x/V-1.2) | Latest archived integrated firmware |
| [`V-1.x/test`](V-1.x/test) | Component, communication and radiation-detector experiments |
| [`docs`](docs) | Wiring, logs and showcase files |
| [`images`](images) | PCB renders and photographs |

## Build requirements

The integrated sketches use Arduino IDE and the following libraries:

- `Adafruit_BMP280`
- `RF24` / `nRF24L01`
- `TroykaMQ`
- `basicMPU6050`
- `SD`, `SPI`, `Wire` and `SoftwareSerial`

Before compiling, select the sketch that matches the hardware revision and verify its pin assignments. MQ-series readings depend strongly on calibration and operating conditions and should be treated as experimental measurements.

Credentials in the archived Wi-Fi/API test sketch have been replaced with `YOUR_...` placeholders. Keep real credentials outside version control.

## Author and usage

Developed and maintained by **Vladimir Chapliy**. Contact: `v.chapliy.dev@gmail.com`.

The source and project materials are published for portfolio and educational review. No open-source license is granted; contact the author before reusing substantial parts of the project, and provide attribution when permission is given.
