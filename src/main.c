#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_Matrix_S1_1, motorD,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_2, motorE,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_3, motorF,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_4, motorG,        tmotorMatrix, openLoop)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_3, servo3,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma debuggerWindows("joystickGame");

#include "JoystickDriver.c"
#include "definitions.h"
#include "math.c"
#include "teleop.c"

bool Running = true;

/*
* Initialize the Robot and ensure that the software is ready to operate.
*/
void Init()
{
	nVolume = 4; // Maximum Volume

	ControllerA.ControllerID = 0;
	ControllerB.ControllerID = 1;
	Init_Teleop();
}

/*
* Ends the current Robot Mode.
*/
void EndState()
{
	Running = false;
}

/*
* Call the main update functions of all the inuse functionality
* Update the current mode that the robot is using. Autonomous/Drive
*/
void Update()
{
	alive();

	Update_Teleop(); // Update Drive Mode
	if (ControllerA.Buttons.Start == ButtonState_Pressed) EndState();

	if (ControllerA.Buttons.LeftStick == ButtonState_Active) playImmediateTone(400, 1); // Input Test aka Horn
}

task main
{
	Init();
	while (Running)
	{
		Update();
		sleep(2);
	}
	EndState();
}