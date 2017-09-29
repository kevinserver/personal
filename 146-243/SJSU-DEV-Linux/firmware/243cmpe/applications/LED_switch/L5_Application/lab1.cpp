


#include <stdio.h>
#include "lab1.hpp"
#include "rtc_alarm.h"
#include "rtc.h"
#include "file_logger.h"
#include "io.hpp"
#include "c_tlm_var.h"
#include "io.hpp"
#include "wireless.h"
#include "uart0.hpp"

LED_task::LED_task() :
	scheduler_task("lab1_LED", 4 * 512, PRIORITY_HIGH)
{

}

bool LED_task::init(void)
{
	LPC_PINCON->PINSEL1 &= ~(3 << 4);
	LPC_PINCON->PINSEL4 &= ~(3 << 26);

	LPC_GPIO2->FIODIR &= ~(1 << 2); //P2.2 input
	LPC_GPIO2->FIODIR |= (1 << 3);  //P2.3 output
	// printf("setup complete.\n");

	return true;
}

bool LED_task::run(void *p)
{
	if (LPC_GPIO2->FIOPIN & (1 << 2))
	{
		LPC_GPIO2->FIOSET |= (1 << 3);
	}
	else
	{
		LPC_GPIO2->FIOCLR |= (1 << 3);
	}

	return true;
}