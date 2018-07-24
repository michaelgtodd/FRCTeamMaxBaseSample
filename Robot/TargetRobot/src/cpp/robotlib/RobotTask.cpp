#include "robotlib/RobotTask.h"
#ifndef WIN32
#include "WPILib.h"
#include "pthread.h"
#else
#define NOMINMAX
#include <Windows.h>
#include <algorithm>
#endif
#include "robotlib/RobotDataStream.h"
#include <math.h>
#include <iostream>
#include "Robot.h"

std::vector<RobotTask*> TaskSchedule::TaskList;

void TaskSchedule::AddTask(RobotTask* task, std::string taskname, uint32_t period)
{
	TaskList.push_back(task);
	task->ExecInit(taskname, period);
}

void TaskSchedule::SetTaskPriorty(int priority, std::string taskname)
{
#ifndef WIN32
	sched_param sch;
	sch.sched_priority = priority;

	if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &sch) != 0)
	{
		std::cout << "Failed to set task: " << taskname << " priority: " << priority << " Error: " << " " << strerror(errno) << std::endl;
	}
	else {
		std::cout << "Set priority for task: " << taskname << " priority: " << priority << std::endl;
	}
#endif
}

void TaskSchedule::LaunchTasks()
{
	TaskSchedule::SetTaskPriorty(99, "DS_Task");

	RobotLog::LogInfo("Starting tasks");
	int priority = 80;
	for (std::vector<RobotTask*>::iterator i = TaskList.begin();
		i != TaskList.end();
		i++)
	{
		(*i)->Launch(priority);
		priority--;
	}
}

std::string RobotTask::GetTaskName()
{
	return taskname_;
}

uint32_t RobotTask::GetTaskPeriod()
{
	return task_period_;
}

void RobotTask::ExecInit(std::string taskname, uint32_t task_period)
{
	taskname_ = taskname;
	uint32_t capped_period = std::min(task_period, (uint32_t) 200);
	capped_period = std::max((uint32_t) 1, capped_period);
	task_period_ = capped_period;

	Init();
}

uint32_t RobotTask::getTimeMS()
{
#ifndef WIN32
	return (uint32_t)(Timer::GetFPGATimestamp() * 1000.0);
#else
	return timeGetTime();
#endif
}

void RobotTask::Launch(int priority)
{
	RobotLog::LogInfo("Launching: " + taskname_);
	running_thread = std::thread(&RobotTask::ThreadProcess, this);
	TaskSchedule::SetTaskPriorty(priority, taskname_);
}

void RobotTask::ThreadProcess()
{
	while (true)
	{
		uint32_t loopStartMS = getTimeMS();
		
		if (RobotState::IsOperatorControl() && RobotState::IsEnabled())
		{
			Run();
		}
		else if (RobotState::IsAutonomous() && RobotState::IsEnabled())
		{
			Autonomous();
		}
		else
		{
			Disable();
		}
		Always();

		uint32_t loopEndMS = getTimeMS();

		lastLoopEndMS = loopEndMS;

		uint32_t loopElapsedTimeMS = (uint32_t)((loopEndMS - loopStartMS));
		uint32_t minsleep = std::max((int32_t)(1000 / task_period_) - (int32_t)loopElapsedTimeMS, (int32_t) 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(minsleep));
	}
}
