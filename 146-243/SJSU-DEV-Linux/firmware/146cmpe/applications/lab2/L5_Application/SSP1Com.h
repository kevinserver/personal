#ifndef SSP1COM_H_
#define SSP1COM_H_

#include "scheduler_task.hpp"
#include "shared_handles.h"
#include "uart3.hpp"
#include "FreeRTOS.h"
#include "semphr.h"

class SSP1Com
{
public:
	SSP1Com();
	bool init(void);
	// bool run(void *p);
	bool select_flash();
	bool deselect_flash();
	uint8_t flashExchange(uint8_t out);
	void read_id();
};

//test class
class flashTest : public scheduler_task 
{
public:
	flashTest();
	bool init(void);
	bool run(void *p);
private:
	SSP1Com * flash;
};











#endif /* SSP1COM_H_ */