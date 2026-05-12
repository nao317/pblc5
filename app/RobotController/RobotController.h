#pragma once /* ヘッダファイルの重複読み込み防止 */

#include "../sensors/SensorData.h"
#include "../motion/GaitParameters.h"

/* RobotController クラスを定義・宣言 */
class RobotController {
	/* RobotControllerクラス外からのアクセスが可能 */
	public:
		void setup();
		void update();
	/* RobotControllerクラス内でのみアクセスが可能 */
	private:
		SensorData sensorData;
		GaitParameters gaitParams;

		void readSensors();
		void updateState();
		void updateGaitParameters();
};

