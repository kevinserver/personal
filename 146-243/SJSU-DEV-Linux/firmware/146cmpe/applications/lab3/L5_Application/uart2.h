

#ifndef UART2_H_
#define UART2_H_


#include "scheduler_task.hpp"
#include "shared_handles.h"
// #include "uart3.hpp"
#include "examples/rn_xv_task.hpp"
#include "FreeRTOS.h"
#include "semphr.h"

class uart2
{
public:
	uart2(uint32_t baud = 38400);
	bool init(void);
	void set_DLM_DLL(uint32_t baud);
	uint8_t getChar();
	void putChar(uint8_t byte);
private:
	uint32_t baudrate;
};

class uart2_test : public scheduler_task
{
public:
	uart2_test(uint32_t baud = 38400);
	bool init(void);
	bool run(void *p);

private:
	uart2 * uart_test;
};








#endif /* UART2_H_ */