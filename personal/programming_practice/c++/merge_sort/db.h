#include "linked.h"

class db : public node
{
public:
	db();
	~db();
	linked *head;
	linked *tail;
};