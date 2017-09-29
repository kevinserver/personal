#ifndef LAB1_HPP_
#define LAB1_HPP_

#include "scheduler_task.hpp"
#include "shared_handles.h"
#include "uart3.hpp"
#include "examples/rn_xv_task.hpp"
#include "FreeRTOS.h"
#include "semphr.h"



class LED_task : public scheduler_task
{
public:
	LED_task();
	bool init(void);
	bool run(void *p);
};







#endif /* LAB1_HPP_ */