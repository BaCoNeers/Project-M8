#include "controller.c"

// :: Variables ::
Controller ControllerA;
Controller ControllerB;
int MotorSpeed = 50;

// :: Methods ::

void Init_Teleop()
{
	// : Reset Motors :
	/*
	intrinsic void memset(void *pToBuffer, const char nValue, const short nNumbOfBytes)
	asm(opcdSystemFunctions, byte(sysFuncMemSet),
	variableRefVoidPtr(pToBuffer),
	variable(nValue),
	variable(nNumbOfBytes));
	*/
}

/*
* Returns the motor speed defined by specific button states
* Returns the value for either Pressed or Active button states
* bA (Button1), bB (Button2), iA (Motor Value1), iB (Motor Value2), def (Default Motor Value)
*/
signed char Map(byte &bA, byte &bB, signed char iA, signed char iB, signed char def)
{
return bA == ButtonState_Active ? iA : (bB == ButtonState_Active ? iB : def);
}
int count = 0;
int speed = 5;
bool TeleopActive = true;
/*
* Updates Teleop
*/
void Update_Teleop()
{
	// Update Controllers
	Update_Controller(ControllerA);

	// : Calculate Motor Speed
	/*
	// Clamped squared interpolation for the drive motors
	float rotation = -ControllerA.RightStick.x;
	if(rotation*rotation < 0.0025) rotation = 0;
	else rotation *= (rotation<0) ? -rotation : rotation; // Same sign, Squared Value

	// Each wheel shares a +- Speed Value depending on the LeftStick Y Axis
	// The value is manipulated by the +- Linear Interpolated Value of the Rotation
	float speed = ControllerA.RightStick.x;
	float leftmotorspeed = lerp(speed,-speed, rotation);
	float rightmotorspeed = -lerp(speed,-speed, rotation);
	*/

	if (ControllerA.Buttons.X == ButtonState_Pressed)
	{
		MotorSpeed = (MotorSpeed == 100) ? 50 : 100;
	}

	if (ControllerA.Buttons.Back == ButtonState_Active && ControllerA.Buttons.Start == ButtonState_Pressed ||
		ControllerB.Buttons.Back == ButtonState_Active && ControllerB.Buttons.Start == ButtonState_Pressed) TeleopActive = !TeleopActive;

	// Only code that works... :(
	if (ControllerA.Buttons.Y == ButtonState_Active || ControllerA.Buttons.A == ButtonState_Active)
	{
		if (ControllerA.Buttons.A == ButtonState_Active)
		{
			motor[Motor_Actuator_Left] = -100;
			motor[Motor_Actuator_Right] = -100;
		} else {
			motor[Motor_Actuator_Left] = 100;
			motor[Motor_Actuator_Right] = 100;
		}
	}
	else if (ControllerA.Buttons.X == ButtonState_Active || ControllerA.Buttons.B == ButtonState_Active)
	{
		if (ControllerA.Buttons.X == ButtonState_Active)
		{
			motor[Motor_Actuator_Left] = -100;
		} else {
			motor[Motor_Actuator_Right] = -100;
		}
	}
	else
	{
		motor[Motor_Actuator_Left] = 0;
		motor[Motor_Actuator_Right] = 0;
	}

	if (TeleopActive)
	{
		// Clamped squared interpolation for the drive motors
		float rotation = -ControllerA.RightStick.x * 0.75;
	rotation *= (rotation<0) ? -rotation : rotation;

		// : Calculate Motor Speed
		float leftmotorspeed = -lerp(ControllerA.LeftStick.y, -ControllerA.LeftStick.y, rotation);
		float rightmotorspeed = lerp(ControllerA.LeftStick.y, -ControllerA.LeftStick.y, -rotation);

		// : Mapping of Servos and Motors to Sticks and Buttons :
		motor[Motor_Drive_Left_1] = MotorSpeed * leftmotorspeed;
		motor[Motor_Drive_Left_2] = MotorSpeed * leftmotorspeed;
		motor[Motor_Drive_Right_1] = MotorSpeed * rightmotorspeed;
		motor[Motor_Drive_Right_2] = MotorSpeed * rightmotorspeed;
	}
	else
	{
		playImmediateTone(300,10);
		motor[Motor_Drive_Left_1] = 0;
		motor[Motor_Drive_Left_2] = 0;
		motor[Motor_Drive_Right_1] = 0;
		motor[Motor_Drive_Right_2] = 0;
	}
}
