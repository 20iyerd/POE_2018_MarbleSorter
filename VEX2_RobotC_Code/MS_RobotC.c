#pragma config(Motor,  port2,           feeder,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           wallTilt,      tmotorServoStandard, openLoop)
#pragma config(Motor,  port4,           wallTurn,      tmotorServoStandard, openLoop)
#pragma config(Motor,  port5,           waterMotor,    tmotorVex393_MC29, openLoop)
#pragma config(UART_Usage, UART2, User_Control)

#define glassBlue 1
#define glassCatsEye 2
#define steelSilver 3

#define servoBlue -100
#define servoCatsEye -100
#define servoSilver -100

#define wallTiltAngle 127

task UARTReceive();

int rcvChar;
int testRcv;

task main()
{
	int marbleSign;
	
	setBaudRate(uartTwo, baudRate9600);

	while (getChar(uartTwo) != -1) // Purge existing chars from buffer
	{}
	
	while(true){
		
		wait(2); //TODO - why and how much, new func?
		startMotor(feeder, 28);
		
		startTask(UARTReceive);
		
		marbleSign = rcvChar;
		
		switch(marbleSign)
		{
			case glassBlue:
			{
				testRcv=glassBlue;
				setServo(wallTurn, servoBlue); wait(3);
				setServo(wallTurn, 0);	wait(1);
				
				setServo(wallTilt, wallTiltAngle);	wait(3);
				setServo(wallTilt, 0);
			}
			case glassCatsEye:
			{
				setServo(wallTurn, servoCatsEye);	wait(3);
				setServo(wallTurn, 0);	wait(1);
				
				setServo(wallTilt, wallTiltAngle);	wait(3);
				setServo(wallTilt, 0);
			}
			case steelSilver:
			{
				setServo(wallTurn, servoSilver);	wait(3);
				setServo(wallTurn, 0);	wait(1);
				
				setServo(wallTilt, wallTiltAngle);	wait(3);
				setServo(wallTilt, 0);
			}
			default:
				break;
		}

		wait(1);
		startMotor(waterMotor, -20);
		wait(2);
		startMotor(waterMotor, 20);
		wait(2);
		
	}
}

task UARTReceive()
{
	while (true)
	{
		// Loop forever getting characters from the "receive" UART. Validate that they arrive in the expected sequence.

		rcvChar = getChar(uartTwo);
		if (rcvChar == -1)// No character available
		{
			wait1Msec(2); // Don't want to consume too much CPU time. Waiting eliminates CPU consumption for this task.
			continue;
		}
	}
}
