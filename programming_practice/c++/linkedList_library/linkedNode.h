#ifndef LINKEDNODE.H
#define LINKEDNODE.H

#include <stdio>
#include <stdlib>
#include "linkedList.h"

class linkedNode : public linkedList
{
public:
	linkedNode();
	linkedNode(int numBranches);
	~linkedNode();
	linkedNode* prev;
	linkedNode* next[branches];
private:
	int branches;
};



#endif LINKEDNODE.H