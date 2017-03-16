#ifndef LINKEDLIST.H
#define LINKEDLIST.H

#include <stdio>
#include <stdlib>
#include "linkedNode.h"

class linkedList
{
public:
	linkedList();
	linkedList(int numBranches);
	~linkedList();
	void addNodeFront(); 					//add comdition for one branch per node
	void addNodeEnd();						//add comdition for one branch per node
	void addNodeAfter(linkedNode* node);	//add comdition for one branch per node
	void removeNode(linkedNode* node);		//add comdition for one branch per node

	//setters
	void set_numNodes(int);

	//getters
	int get_numNodes();

	linkedNode* head;
	linkedNode* tail; //if branches > 1, tail will not be used
private:
	int numNodes;
	int branches;
};




#endif //LINKEDLIST.H