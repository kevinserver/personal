
#include <stdio.h>
#include "uart2.h"

#define CPU_CLOCK 48000000


uart2::uart2(uint32_t baud)
{
	baudrate = baud;
	// init();
}

bool uart2::init(void)
{
	//pins
	BIT(LPC_SC->PCONP).b24 = 1;
	BIT(LPC_SC->PCLKSEL1).b17_16 = 1; // PCLK = CLK

	set_DLM_DLL(baudrate);

	BIT(LPC_PINCON->PINSEL4).b17_16 = 2;
	BIT(LPC_PINCON->PINSEL4).b19_18 = 2;

	BIT(LPC_UART2->LCR).b0 = 1;

	return true;
}

void uart2::set_DLM_DLL(uint32_t baud)
{
	LPC_UART2->LCR = (1 << 7);

	uint32_t regValue = CPU_CLOCK / (16 * baud) + 0.5;

	LPC_UART2->DLM = (regValue >> 8);
	LPC_UART2->DLL = regValue & 0xFF;

	LPC_UART2->LCR = 3;
}

uint8_t uart2::getChar()
{
	while (!(LPC_UART2->LSR & 1)); //poll for character
	return LPC_UART2->RBR;
}

void uart2::putChar(uint8_t byte)
{
	LPC_UART2->THR = byte;
	while (!(LPC_UART2->LSR & (1 << 6)));
}



//test class
uart2_test::uart2_test(uint32_t baud) :
	scheduler_task("UART2_test_task", 4 * 512, PRIORITY_HIGH)
{
	uart_test = new uart2(baud);
	setRunDuration(250);
}

bool uart2_test::init(void)
{
	uart_test->init();
	return true;
}

bool uart2_test::run(void *p)
{
	uart_test->putChar('A');
	printf("Received character: %c\n", uart_test->getChar());
	return true;
}
