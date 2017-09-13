#include linkedList.h


linkedList::linkedList() 
{
	head = NULL;
	tail = NULL;
	numNodes = 0;
	treeType = "normal"; //monary doubly-linked list
	branches = 1;
}
linkedList::linkedList(int numBranches, string type)
{
	branches = numBranches;
	numNodes = 0;
	treeType = type;
	head = NULL;
	tail = NULL;
}
linkedList::~linkedList()
{
	linkedNode* deleter = head;
	switch(treeType)
	{
		case "normal":
			while (deleter != tail)
			{
				deleter = deleter->next;
				delete deleter->prev;
			}
			delete head;
			delete tail;
			break;
		case "binary":

			break;
	}
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
	switch(treeType)
	{
	case "normal":
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
		break;
	case "binary":

		break;
	}
}
void addChild(linkedNode* node)
{
	linkedNode* newNode = new linkedNode(numBranches);

	newNode->prev = node;
}
void set_numNodes(int num)
{
	numNodes = num;
}
int get_numNodes()
{
	return numNodes;
}
