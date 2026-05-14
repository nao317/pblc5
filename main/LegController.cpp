#include "LegController.h"

void LegController::update(LegTarget* targets) {

    for(int i = 0; i < 4; i++) {

        // 仮実装
        Serial.print("Leg ");
        Serial.print(i);
        Serial.print(": ");

        Serial.print(targets[i].x);
        Serial.print(", ");

        Serial.print(targets[i].y);
        Serial.print(", ");

        Serial.println(targets[i].z);
    }
}
