#include linkedList.h


linkedList::linkedList() 
{
	head = NULL;
	tail = NULL;
	numNodes = 0;
	branches = 1;
}
linkedList::linkedList(int numBranches)
{
	branches = numBranches;
	numNodes = 0;
	head = NULL;
	tail = NULL;
}
linkedList::~linkedList()
{
	linkedNode* deleter = head;
	while (deleter != tail)
	{
		deleter = deleter->next;
		delete deleter->prev;
	}
	delete head;
	delete tail;
}
void linkedList::addNodeFront()
{
	linkedNode* newNode = new linkedNode;

	if (head == NULL)
	{
		head = newNode;
		tail = newNode;
	}
	else 
	{
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
	}
	numNodes++;
}
void linkedList::addNodeEnd()
{
	linkedNode* newNode = new linkedNode;

	if (tail == NULL)
	{
		head = newNode;
		tail = newNode;
	}
	else 
	{
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	numNodes++;
}
void linkedList::addNodeAfter(linkedNode* node)
{
	linkedNode* newNode = new linkedNode;

	if (head == NULL)
	{
		head = newNode;
		tail = newNode;
	}
	else 
	{
		newNode->next = node->next;
		node->next->prev = newNode;
		newNode->prev = node;
		node->next = newNode;
		if (tail == node)
		{
			tail = newNode;
		}
	}
	numNodes++;
}
void linkedList::removeNode(linkedNode* node)
{
	if (numNodes == 0)
	{
		return;
	}
	else if (numNodes == 1)
	{
		head = NULL;
		tail = NULL;
		delete node;
	}
	else
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
		if (head == node)
		{
			head = node->next;
		}
		if (tail == node)
		{
			tail = node->prev;
		}
		delete node;
	}
	numNodes--;
}
void set_numNodes(int num)
{
	numNodes = num;
}
int get_numNodes()
{
	return numNodes;
}