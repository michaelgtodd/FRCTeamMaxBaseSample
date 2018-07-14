#pragma once

namespace RobotState 
{
	bool IsOperatorControl();
	bool IsEnabled();
	bool IsAutonomous();
};

namespace frc
{
	class SampleRobot
	{
	public:
		void virtual RobotInit() = 0;
		void virtual Disabled() = 0;
		void virtual Autonomous() = 0;
		void virtual OperatorControl() = 0;
		void virtual Test() = 0;
	};
}