# 前期PBL C5班

# Quadruped Robot Project

段差昇降可能な4足歩行ロボットの開発プロジェクト。

---

# Features

- 4足歩行
- 段差昇降
- 姿勢制御
- 歩行パターン切替
- IMUによるバランス補正
- 距離センサによる段差検知
- 拡張可能なモジュール構成

---

# Architecture

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
│   ├── IMU
│   ├── DistanceSensor
│   └── FootSensor
│
├── Hardware
│   ├── ServoDriver
│   └── PWMDriver
│
├── Control
│   ├── PIDController
│   └── BalanceController
│
└── System
    ├── StateMachine
    ├── Config
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
│   │   └── TrajectoryGenerator.cpp
│   │
│   ├── sensors/
│   │   ├── IMUSensor.h
│   │   ├── IMUSensor.cpp
│   │   ├── DistanceSensor.h
│   │   ├── DistanceSensor.cpp
│   │   ├── FootSensor.h
│   │   └── FootSensor.cpp
│   │
│   ├── hardware/
│   │   ├── ServoDriver.h
│   │   ├── ServoDriver.cpp
│   │   ├── PWMDriver.h
│   │   └── PWMDriver.cpp
│   │
│   ├── control/
│   │   ├── PIDController.h
│   │   ├── PIDController.cpp
│   │   ├── BalanceController.h
│   │   └── BalanceController.cpp
│   │
│   ├── system/
│   │   ├── StateMachine.h
│   │   ├── StateMachine.cpp
│   │   ├── Config.h
│   │   └── Logger.h
│   │
│   └── utils/
│       ├── Vector3.h
│       ├── MathUtils.h
│       └── Constants.h
│
└── docs/
    ├── architecture.md
    ├── gait-design.md
    └── hardware.md
```

---

# Design Philosophy

## 1. Single Responsibility

1クラスにつき1責務を基本とする。

例：

- センサ取得
- サーボ制御
- 歩行生成
- 姿勢制御
- 状態管理

を分離する。

---

## 2. Hardware Abstraction

サーボ角度を直接扱わず、
足先座標によって制御する。

### Bad

```cpp
servo.write(120);
```

### Good

```cpp
leg.moveTo(x, y, z);
```

---

## 3. Update Loop Architecture

Arduinoの `loop()` をゲームループ的に扱う。

```cpp
void loop() {
    robot.update();
}
```

内部では：

```cpp
imu.update();
balance.update();
gait.update();
```

のように各モジュールを更新する。

---

# Main Components

---

# RobotController

全体制御を行う最上位クラス。

## Responsibilities

- 初期化
- 状態管理
- 各モジュール更新
- 非常停止

## Example

```cpp
class RobotController {
public:
    void begin();
    void update();

private:
    GaitController gait;
    BalanceController balance;
    IMUSensor imu;
};
```

---

# LegController

1本の脚を制御する。

## Responsibilities

- 股関節制御
- 膝制御
- 脚先移動

## Example

```cpp
class LegController {
public:
    void moveTo(float x, float y, float z);

private:
    ServoDriver hip;
    ServoDriver thigh;
    ServoDriver knee;
};
```

---

# GaitController

歩行パターンを生成する。

## Supported Gaits

- Trot
- Crawl
- Bound
- Climbing

## Example

```cpp
class GaitController {
public:
    void update();
};
```

---

# TrajectoryGenerator

脚先軌道を生成する。

## Example

```cpp
Vector3 generateStepTrajectory(float phase);
```

## Trajectory Image

```txt
      ／￣＼
_____/      \_____
```

---

# IMUSensor

姿勢角を取得する。

## Responsibilities

- Pitch取得
- Roll取得
- 姿勢更新

## Example

```cpp
class IMUSensor {
public:
    void update();

    float getPitch();
    float getRoll();
};
```

---

# BalanceController

姿勢安定化を行う。

## Responsibilities

- PID制御
- 姿勢補正
- 重心補正

## Example

```cpp
class BalanceController {
public:
    void update(float pitch, float roll);
};
```

---

# PIDController

汎用PID制御クラス。

## Example

```cpp
class PIDController {
public:
    float compute(float target, float current);
};
```

---

# StateMachine

ロボット状態管理。

## Example

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

# Step Climbing Flow

```txt
DistanceSensor
    ↓
段差検知
    ↓
StateMachine
    ↓
Climbingモード
    ↓
Trajectory変更
```

---

# Future Extensions

- Inverse Kinematics
- SLAM
- ROS2 Integration
- Camera Recognition
- Autonomous Navigation

---

# Development Phases

## Phase 1

サーボ単体動作

## Phase 2

脚1本制御

## Phase 3

4脚同期

## Phase 4

IMU安定化

## Phase 5

段差検知

## Phase 6

段差昇降

---

# Main Loop Example

```cpp
#include "app/RobotController.h"

RobotController robot;

void setup() {
    robot.begin();
}

void loop() {
    robot.update();
}
```

---

# Important Concept

このプロジェクトでは、

```txt
「サーボ角度」ではなく
「足先座標」
```

で制御する。

これにより：

- 歩行生成
- 段差昇降
- バランス制御
- 逆運動学

を統一的に扱える。

---