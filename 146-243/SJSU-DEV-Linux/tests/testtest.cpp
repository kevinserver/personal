#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <typeinfo>

#include "mockFiles/mocktestfile.cpp"

using namespace cgreen;




Ensure(sensor_is_read_correctly)
{
	always_expect(readSensorValue, will_return(0));
	assert_that(readSensorValue(), is_equal_to(0));
}

Ensure(PWM_returns_neg_1)
{
	always_expect(readSensorValue, will_return(150));
	assert_equal(getMotorPWM(), -1);
}

Ensure(PWM_returns_8) 
{
	always_expect(readSensorValue, will_return(25));
	assert_equal(getMotorPWM(), 8);
}

Ensure(PWM_returns_9)
{
	always_expect(readSensorValue, will_return(90));
	assert_equal(getMotorPWM(), 9);
}

TestSuite *PWM_test()
{
	TestSuite *suite = create_test_suite();
	add_test(suite, sensor_is_read_correctly);
	add_test(suite, PWM_returns_neg_1);
	add_test(suite, PWM_returns_8);
	add_test(suite, PWM_returns_9);
	return suite;
}

int main(int argc, char const *argv[])
{
	TestSuite *suite = create_test_suite();

	add_suite(suite, PWM_test());



	return run_test_suite(suite, create_text_reporter());;
}