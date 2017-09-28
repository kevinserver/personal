#include "my_eint3.h"
#include "rtc_alarm.h"
#include "rtc.h"
#include "file_logger.h"
#include "io.hpp"
#include "c_tlm_var.h"
#include "wireless.h"
#include "uart0.hpp"


bool int_flag0[32] = {0};
bool int_flag2[32] = {0};
// bool SW2_flag = 0;

extern "C" void EINT3_IRQHandler(void)
{
	u0_dbg_printf("handler called.\n");
	for (uint8_t i = 0; i < 32; i++)
	{
		int_flag0[i] = (LPC_GPIOINT->IO0IntStatR | LPC_GPIOINT->IO0IntStatF);
		if(int_flag0[i]) LPC_GPIOINT->IO0IntClr = (1 << i);
		int_flag2[i] = (LPC_GPIOINT->IO2IntStatR | LPC_GPIOINT->IO2IntStatF);
		if(int_flag2[i]) LPC_GPIOINT->IO2IntClr = (1 << i);
	}
}

void register_interrupt_eint3(uint8_t port, uint8_t pin, edgeType_t edgeType)
{
	//uint32_t * tempReg = (uint32_t*)INTERRUPT_DIRECTION(port);
	*(INTERRUPT_DIRECTION(port)) &= ~(1 << pin);
	//tempReg = (uint32_t*)INTERRUPT_EDGE(port, pin);
	*(INTERRUPT_EDGE(port, edgeType)) |= (1 << pin);
	printf("Initializing Port %d, Pin %d.\n", port, pin);
}

// void register_interrupt_port2(uint8_t pin, edgeType_t edgeType)
// {
// 	LPC_GPIO2->FIODIR &= ~(1 << pin);
// 	*edgeType = (1 << pin);
// }







SW1_IR::SW1_IR(uint8_t pinNum, uint8_t portNum) : 
	scheduler_task("SW1 task", 4 * 512, PRIORITY_LOW)
{
	pin = pinNum;
	port = portNum;
}

bool SW1_IR::init(void)
{
	register_interrupt_eint3(port, pin, rising_edge);
	return true;
}

bool SW1_IR::run(void * p)
{
	if (int_flag2[pin])
	{
		u0_dbg_printf("SW1 pressed.\n");
		int_flag2[pin] = 0;
		// LPC_GPIOINT->IO2IntClr = (1 << pin);
	}
	return true;
}



SW2_IR::SW2_IR(uint8_t pinNum, uint8_t portNum) : 
	scheduler_task("SW2 task", 4 * 512, PRIORITY_LOW)
{
	pin = pinNum;
	port = portNum;
}

bool SW2_IR::init(void)
{
	register_interrupt_eint3(port, pin, rising_edge);
	return true;
}

bool SW2_IR::run(void * p)
{
	if (int_flag2[pin])
	{
		u0_dbg_printf("SW2 pressed.\n");
		int_flag2[pin] = 0;
		// LPC_GPIOINT->IO2IntClr = (1 << pin);
	}
	return true;
}