
#include <stdio.h>
#include "SSP1Com.h"
#include "rtc_alarm.h"
#include "rtc.h"
#include "file_logger.h"
#include "io.hpp"
#include "c_tlm_var.h"
#include "io.hpp"
#include "wireless.h"
#include "uart0.hpp"

void checkBits(uint8_t back);

SSP1Com::SSP1Com() //:
	//scheduler_task("flash_communication", 4 * 512, PRIORITY_HIGH)
{
	
}

bool SSP1Com::init(void)
{
	LPC_SC->PCONP |= (1 << 10); //ssp
	LPC_SC->PCLKSEL0 &= ~(3<<20); 	//enable ssp clk
	LPC_SC->PCLKSEL0 |= (1<<20);	//SCLK = CLK
	LPC_PINCON->PINSEL0 |= 0xA8000; //set pins for ssp
	// LPC_PINCON->PINSEL0 &= ~(0xAB000);
	LPC_GPIO0->FIODIR |= (1 << 6);
	LPC_GPIO0->FIOSET |= (1 << 6);
	LPC_SSP1->CR0 = 7;
	LPC_SSP1->CR1 = 2;
	LPC_SSP1->CPSR = 8; //set sclk scalar

	printf("INITIALIZED.\n");

	return true;
}

bool SSP1Com::select_flash()
{

	//add checks for other devices being selected once they are implemented
	LPC_GPIO0->FIOCLR |= (1 << 6);

	return true;
}

bool SSP1Com::deselect_flash()
{
	LPC_GPIO0->FIOSET |= (1 << 6);

	return true;
}

uint8_t SSP1Com::flashExchange(uint8_t out)
{
	LPC_SSP1->DR = out;
	while (LPC_SSP1->SR & (1 << 4));
	return LPC_SSP1->DR;
}

void SSP1Com::read_id()
{
	select_flash();

	//Device Signature
	uint8_t opcode = 0x9F;
	flashExchange(opcode);
	printf("Device Signature: Sending opcode 0x%X\n", opcode);

	uint8_t back = flashExchange(0xFF);
	printf("\tManufacturer ID: 0x%X\n", back);

	back = flashExchange(0xFF);
	printf("\tDevice ID (1): 0x%X\n", back);

	back = flashExchange(0xFF);
	printf("\tDevice ID (2): 0x%X\n", back);

	back = flashExchange(0xFF);
	printf("\tExtended device information: 0x%X\n", back);

	//stop Device signature reading
	deselect_flash();

	select_flash();

	//Status Register
	opcode = 0xD7;
	flashExchange(opcode);
	printf("Status Register: Sending opcode 0x%X\n", opcode);

	back = flashExchange(0xFF);
	printf("\tByte 1: 0x%X\n", back);
	
	checkBits(back);

	back = flashExchange(0xFF);
	printf("\tByte 2: 0x%X\n", back);

	checkBits(back);

	printf("\n");

	deselect_flash();
}


flashTest::flashTest() : 
	scheduler_task("flash_communication", 4 * 512, PRIORITY_HIGH)
{
	flash = new SSP1Com();
	setRunDuration(10000);
}

bool flashTest::init(void)
{
	flash->init();
	return true;
}

bool flashTest::run(void *p)
{
	flash->read_id();
	return true;
}



void checkBits(uint8_t back)
{
	if(back & (1 << 7))
	{
		printf("\t\tBit 7 is 1. Ready.\n");
	}
	else printf("\t\tBit 7 is 1. Busy.\n");

	if(back & (1 << 6))
	{
		printf("\t\tData in memory does not match data in buffer.\n");
	}
	else printf("\t\tData in memory matches data in buffer.\n");

	if(back & (1 << 5))
	{
		printf("\t\tBit 5 is set.\n");
	}
	else printf("\t\tBit 5 is not set.\n");

	if(back & (1 << 4))
	{
		printf("\t\tBit 4 is set.\n");
	}
	else printf("\t\tBit 4 is not set.\n");

	if(back & (1 << 3))
	{
		printf("\t\tBit 3 is set.\n");
	}
	else printf("\t\tBit 3 is not set.\n");

	if(back & (1 << 2))
	{
		printf("\t\tBit 2 is set.\n");
	}
	else printf("\t\tBit 2 is not set.\n");

	if(back & (1 << 1))
	{
		printf("\t\tProtection is enabled.\n");
	}
	else printf("\t\tProtection is disabled.\n");

	if(back & (1 << 0))
	{
		printf("\t\tConfigured for 256-bytes.\n");
	}
	else printf("\t\tConfigured for 264-bytes.\n");
}