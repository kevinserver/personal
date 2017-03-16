#include "linkedNode.h"

linkedNode::linkedNode()
{
	branches = 1;
	prev = NULL;
	next[0] = NULL;

}
linkedNode::linkedNode(int numBranches)
{
	branches = numBranches;
	prev = NULL;
	for (int i = 0; i < branches; i++)
	{
		next[i] = NULL;
	}
}
linkedNode::~linkedNode()
{
	delete next;
	delete [] prev;
}