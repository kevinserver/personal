#ifndef MY_EINT3_H_
#define MY_EINT3_H_

#include <stdlib.h>
#include <stdio.h>

#include "scheduler_task.hpp"
#include "shared_handles.h"
#include "uart3.hpp"
#include "FreeRTOS.h"
#include "semphr.h"
#include "printf_lib.h"

#define RISE0 								&(LPC_GPIOINT->IO0IntEnR)
#define FALL0 								&(LPC_GPIOINT->IO0IntEnF)
#define RISE2								&(LPC_GPIOINT->IO2IntEnR)
#define FALL2								&(LPC_GPIOINT->IO2IntEnF)
#define INTERRUPT_DIRECTION(port)			(port==2) ? &(LPC_GPIO2->FIODIR) : &(LPC_GPIO0->FIODIR)
#define INTERRUPT_EDGE(port, edge) 			(port==2) ? (edge ? FALL2 : RISE2) : (edge ? FALL0 : RISE0)

typedef enum 
{
	rising_edge  = 0,
	falling_edge = 1// : &(LPC_GPIOINT->IO2IntEnF);
} edgeType_t;


void register_interrupt_eint3(uint8_t port, uint8_t pin, edgeType_t edgeType);







class SW1_IR : public scheduler_task
{
public:
	SW1_IR(uint8_t pinNum = 1, uint8_t portNum = 2);
	bool init(void);
	bool run(void * p);
private:
	uint8_t pin;
	uint8_t port;
};

class SW2_IR : public scheduler_task
{
public:
	SW2_IR(uint8_t pinNum = 2, uint8_t portNum = 2);
	bool init(void);
	bool run(void * p);
private:
	uint8_t pin;
	uint8_t port;
};




#endif /* MY_EINT3_H_ */