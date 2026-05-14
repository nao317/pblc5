#include "Arduino.h"
#include "RobotController.h"

RobotController robot; // RobotControllerのインスタンス: robotを宣言

/* セットアップ */
void setup() {
  robot.setup();
}

void loop() {
  robot.update();
}

// /* 書き込み検証用 */

// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   Serial.print("hello\n");
//   delay(1000);
// }
