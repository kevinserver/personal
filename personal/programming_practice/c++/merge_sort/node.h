#include "linked.h"

class node : public linked
{
public:
	node();
	~node();
	node *prev;
	node *next;

};