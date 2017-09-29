
#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include <stdio.h>

using namespace cgreen;

static int readSensorValue()
{
	return (int)mock();
}

static int getMotorPWM()
{
	int sensorValue = readSensorValue();
	if (sensorValue < 0 || sensorValue > 100)
	{
		return -1;
	}
	else if (sensorValue >= 0 && sensorValue < 50)
	{
		return 8;
	}
	else //(sensorValue >= 50 && sensorValue <= 100)
	{
		return 9;
	}
	return 0;
}