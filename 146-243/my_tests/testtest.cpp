#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "mockFiles/mocktestfile.cpp"

using namespace cgreen;

Ensure(sensor_is_read_correctly)
{
	assert_that(readSensorValue(), is_equal_to(50));
}

Ensure(PWM_is_correct)
{
	if (readSensorValue() < 0 || readSensorValue() > 100)
	{
		assert_equal(getMotorPWM(), -1);
	}
	else if (readSensorValue() >= 0 || readSensorValue() < 50)
	{
		assert_equal(getMotorPWM(), 8);
	}
	else //(readSensorValue() >= 50 || readSensorValue() <= 100)
	{
		assert_equal(getMotorPWM(), 9);
	}
}

TestSuite *PWM_test()
{
	TestSuite *suite = create_test_suite();
	add_test(suite, PWM_is_correct);
	return suite;
}

int main(int argc, char const *argv[])
{
	TestSuite *suite = create_test_suite();
	add_suite(suite, PWM_test());



	return run_test_suite(suite, create_text_reporter());;
}