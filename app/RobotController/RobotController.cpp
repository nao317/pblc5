void RobotController::update() {

	/* センサーの値読込 */
	readSensors();

	/* 状態の更新 */
	updateState();

	/* 歩行パラメータの更新 */
	updateGaitParameters();

	gaitController.update(gaitParams);

	legController.update(
		gaitController.getLegTargets()
	);
}
