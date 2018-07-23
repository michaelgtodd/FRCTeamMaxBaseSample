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

void TaskSchedule::AddTask(RobotTask* task, std::string taskname, uint32_t period)
{
	TaskList.push_back(task);
	task->ExecInit(taskname, period);
}

void TaskSchedule::LaunchTasks()
{
	int priority = 99;
#ifndef WIN32
	sched_param sch;
	sch.sched_priority = priority;

	if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &sch) != 0)
	{
		std::cout << "Failed to set task: " << "DS_Task" << " priority: " << priority << " Error: " << " " << strerror(errno) << std::endl;
		RobotLog::LogError("Failed to set task: DS_Task priority: " + std::to_string(priority) + " Error: " + strerror(errno));
	}
	else {
		std::cout << "Set priority for task: " << "DS_Task" << " priority: " << priority << std::endl;
		RobotLog::LogInfo("Set priority for task: DS_Task priority: " + std::to_string(priority));
	}
#endif
	RobotLog::LogInfo("Starting tasks");
	priority = 80;
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

void RobotTask::Launch(int priority)
{
	RobotLog::LogInfo("Launching: " + taskname_);
	running_thread = std::thread(&RobotTask::ThreadProcess, this);
#ifndef WIN32
	sched_param sch;
	sch.sched_priority = priority;

	if (pthread_setschedparam(running_thread.native_handle(), SCHED_FIFO, &sch) != 0)
	{
		std::cout << "Failed to set task: " << taskname_ << " priority: " << priority << " Error: " << " " << strerror(errno) << std::endl;
		RobotLog::LogError("Failed to set task: " + taskname_ + " priority: " + std::to_string(priority) + " Error: " + strerror(errno));
	}
	else {
		std::cout << "Set priority for task: " << taskname_ << " priority: " << priority << std::endl;
		RobotLog::LogInfo("Set priority for task: " + taskname_ + " priority: " + std::to_string(priority));
	}
#endif
}

void RobotTask::ThreadProcess()
{
	while (true)
	{
#ifndef WIN32
		double loopStart = Timer::GetFPGATimestamp();
#else
		double loopStart = timeGetTime() / 1000.0;
#endif
		
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
#ifndef WIN32
		double loopEnd = Timer::GetFPGATimestamp();
#else
		double loopEnd = timeGetTime() / 1000.0;
#endif
		double loopDuration = loopEnd - loopStart;

		uint32_t loopExecutionTimeMS = (uint32_t) loopDuration;

		double current_loop_difference = (loopEnd - last_loop_end) * 1000.0;
		last_loop_end = loopEnd;

		bool slept = false;
		do {
#ifndef WIN32
			double currentTime = Timer::GetFPGATimestamp();
#else
			double currentTime = timeGetTime() / 1000.0;
#endif
			uint32_t loopElapsedTimeMS = (uint32_t)((currentTime - loopStart) * 1000.0);
			if (loopElapsedTimeMS < (1000.0 / task_period_))
			{
				slept = true;
				uint32_t minsleep = std::min(((uint32_t)1000 / task_period_) - loopElapsedTimeMS, (uint32_t) 5);
				std::this_thread::sleep_for(std::chrono::milliseconds(minsleep));
			}
			else
			{
				if(!slept)
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				break;
			}
		} while (true);
	}
}

TaskSchedule taskschedule;
