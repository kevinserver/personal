#ifndef LINKEDNODE_H_
#define LINKEDNODE_H_

#include <stdio>
#include <stdlib>
// #include "linkedList.h"

class linkedNode
{
public:
	linkedNode();
	linkedNode(int numBranches);
	~linkedNode();
	linkedNode* prev;
	linkedNode* next;

	//setters
	void set_branches(int numBranches);

	//getters
	int get_branches();
private:
	int branches;
};



#endif //LINKEDNODE_H_