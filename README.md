# 前期　PBL

Arduino IDE を使用して開発する、
段差昇降対応4足歩行ロボットプロジェクト。

赤外線センサを利用した PID 制御によって、
壁距離制御・段差検知・姿勢補助を行う。

---

# Development Environment

## IDE

- Arduino IDE

## Language

- C++

## Supported Boards

- Arduino Uno
- Arduino Mega
- ESP32
- ESP32-S3

---

# Features

- 4足歩行
- 段差昇降
- PID制御
- 赤外線センサによる距離計測
- IMUによる姿勢安定化
- モジュール分割設計
- クラスベース実装

---

# System Architecture

```txt
Application
│
├── RobotController
│
├── Motion
│   ├── GaitController
│   ├── LegController
│   └── TrajectoryGenerator
│
├── Sensors
│   ├── IRSensor
│   ├── IMUSensor
│   └── FootSensor
│
├── Control
│   ├── PIDController
│   └── BalanceController
│
├── Hardware
│   ├── ServoDriver
│   └── PWMDriver
│
└── System
    ├── StateMachine
    └── Logger
```

---

# Directory Structure

```txt
quadruped-robot/
├── src/
│   ├── main.ino
│   │
│   ├── app/
│   │   ├── RobotController.h
│   │   └── RobotController.cpp
│   │
│   ├── motion/
│   │   ├── GaitController.h
│   │   ├── GaitController.cpp
│   │   ├── LegController.h
│   │   ├── LegController.cpp
│   │   ├── TrajectoryGenerator.h
│   │   ├── TrajectoryGenerator.cpp
│   │   ├── GaitParameters.h
│   │   ├── LegTargets.h
│   │   └── BodyPose.h
│   │
│   ├── kinematics/
│   │   ├── InverseKinematics.h
│   │   ├── InverseKinematics.cpp
│   │   ├── ForwardKinematics.h
│   │   └── ForwardKinematics.cpp
│   │
│   ├── sensors/
│   │   ├── SensorData.h
│   │   ├── IRSensor.h
│   │   ├── IRSensor.cpp
│   │   ├── IMUSensor.h
│   │   ├── IMUSensor.cpp
│   │   ├── FootSensor.h
│   │   └── FootSensor.cpp
│   │
│   ├── control/
│   │   ├── PIDController.h
│   │   ├── PIDController.cpp
│   │   ├── BalanceController.h
│   │   ├── BalanceController.cpp
│   │   ├── PostureController.h
│   │   └── PostureController.cpp
│   │
│   ├── hardware/
│   │   ├── ServoDriver.h
│   │   ├── ServoDriver.cpp
│   │   ├── PWMDriver.h
│   │   ├── PWMDriver.cpp
│   │   ├── ServoConfig.h
│   │   └── PinConfig.h
│   │
│   ├── system/
│   │   ├── StateMachine.h
│   │   ├── StateMachine.cpp
│   │   ├── RobotState.h
│   │   ├── Logger.h
│   │   ├── Logger.cpp
│   │   ├── TimeManager.h
│   │   └── TimeManager.cpp
│   │
│   ├── utils/
│   │   ├── Vector2.h
│   │   ├── Vector3.h
│   │   ├── MathUtils.h
│   │   ├── LowPassFilter.h
│   │   ├── Constants.h
│   │   └── Types.h
│   │
│   └── config/
│       ├── RobotConfig.h
│       ├── GaitConfig.h
│       └── PIDConfig.h
│
└── docs/
    ├── architecture.md
    ├── gait-design.md
    ├── pid-design.md
    ├── kinematics.md
    └── state-machine.md
```

---

# PID Control Design

赤外線センサを用いて、
対象物との距離を一定に保つ PID 制御を実装する。

---

# PID Flow

```txt
赤外線センサ
    ↓
距離測定
    ↓
PIDController
    ↓
補正量算出
    ↓
脚動作補正
```

---

# PID Formula

PID制御は以下の式を用いる。

:contentReference[oaicite:0]{index=0}

---

# PID Parameters

| Parameter | Description |
|---|---|
| Kp | 比例ゲイン |
| Ki | 積分ゲイン |
| Kd | 微分ゲイン |

---

# Example PID Controller

## PIDController.h

```cpp
#pragma once

class PIDController {
public:
    PIDController(float kp, float ki, float kd);

    float compute(float target, float current);

private:
    float kp;
    float ki;
    float kd;

    float integral;
    float previousError;
};
```

---

## PIDController.cpp

```cpp
#include "PIDController.h"

PIDController::PIDController(
    float kp,
    float ki,
    float kd
) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;

    integral = 0;
    previousError = 0;
}

float PIDController::compute(
    float target,
    float current
) {
    float error = target - current;

    integral += error;

    float derivative =
        error - previousError;

    previousError = error;

    return
        kp * error +
        ki * integral +
        kd * derivative;
}
```

---

# Infrared Sensor Design

赤外線距離センサで壁や段差との距離を測定する。

---

# Example IRSensor Class

## IRSensor.h

```cpp
#pragma once

class IRSensor {
public:
    IRSensor(int pin);

    int readRaw();
    float readDistance();

private:
    int pin;
};
```

---

## IRSensor.cpp

```cpp
#include <Arduino.h>
#include "IRSensor.h"

IRSensor::IRSensor(int pin) {
    this->pin = pin;
}

int IRSensor::readRaw() {
    return analogRead(pin);
}

float IRSensor::readDistance() {
    int value = analogRead(pin);

    return 4800.0 / (value - 20);
}
```

---

# Example Usage

## main.ino

```cpp
#include "sensors/IRSensor.h"
#include "control/PIDController.h"

IRSensor irSensor(A0);

PIDController pid(
    1.0,
    0.01,
    0.1
);

void setup() {
    Serial.begin(115200);
}

void loop() {

    float targetDistance = 20.0;

    float currentDistance =
        irSensor.readDistance();

    float output =
        pid.compute(
            targetDistance,
            currentDistance
        );

    Serial.print("Distance: ");
    Serial.print(currentDistance);

    Serial.print(" Output: ");
    Serial.println(output);

    delay(10);
}
```

---

# Walking Control Concept

PID出力を歩行制御へ反映する。

```txt
PID Output
    ↓
歩幅補正
    ↓
脚位置補正
    ↓
姿勢安定化
```

---

# Recommended Sensor Placement

```txt
        Front

    [IR]      [IR]

        BODY

    [IR]      [IR]

         Rear
```

---

# State Machine Design

```cpp
enum class RobotState {
    Idle,
    Walking,
    Climbing,
    Descending,
    Error
};
```

---

# Development Phases

## Phase 1

赤外線センサ値取得

## Phase 2

PID制御実装

## Phase 3

サーボ制御

## Phase 4

脚1本制御

## Phase 5

4脚同期

## Phase 6

段差昇降

---

# Design Philosophy

## 1. Single Responsibility

1クラス1責務。

---

## 2. Hardware Abstraction

サーボ角度ではなく、
足先座標で制御する。

---

## 3. Update Loop Architecture

```cpp
void loop() {
    robot.update();
}
```

---

# Future Extensions

- Inverse Kinematics
- ROS2 Integration
- SLAM
- Camera Recognition
- Autonomous Navigation

---
