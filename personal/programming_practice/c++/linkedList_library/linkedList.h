#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdio>
#include <stdlib>
#include "linkedNode.h"

class linkedList : public linkedNode
{
public:
	linkedList();
	linkedList(int numBranches, string type);
	~linkedList();
	void addNodeFront(); 					//add comdition for one branch per node
	void addNodeEnd();						//add comdition for one branch per node
	void addNodeAfter(linkedNode* node);	//add comdition for one branch per node
	void removeNode(linkedNode* node);		//add comdition for one branch per node
	void addChild(linkedNode* node);



	//setters
	void set_numNodes(int);

	//getters
	int get_numNodes();

	linkedNode* head;
	linkedNode* tail; //if branches > 1, tail will not be used
private:
	int numNodes;
	string treeType;
	int branches;
};




#endif //LINKEDLIST_H_