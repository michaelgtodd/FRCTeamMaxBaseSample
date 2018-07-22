#pragma once
#include <vector>

class RobotAction
{
public:
	virtual ~RobotAction() = default;

	bool virtual isFinished() = 0;
	void virtual update() = 0;
	void virtual done() = 0;
	void virtual start() = 0;

	std::string getName();

	void setTimeout(uint32_t milliseconds);

private:
	bool isTimeoutExpired();

	uint32_t expired_time;
};

class ParallelAction : RobotAction
{
public:
	void AddAction(RobotAction * Action);
	void AddActions(std::vector<RobotAction *> Actions);

	bool isFinished();
	void update();
	void done();
	void start();

private:
	std::vector<RobotAction *> ActionList;
};

class SerialAction : RobotAction
{
	std::vector<RobotAction *> ActionList;

	void AddAction(RobotAction * Action);
	void AddActions(std::vector<RobotAction *> Actions);

	bool isFinished();
	void update();
	void done();
	void start();
};