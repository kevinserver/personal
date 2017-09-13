#include "linkedNode.h"

linkedNode::linkedNode()
{
	branches = 1;
	prev = NULL;
	next = NULL;

}
linkedNode::linkedNode(int numBranches)
{
	branches = numBranches;
	prev = NULL;
	next = new linkedNode[numBranches];		//any time I make a new node, do this line
	for (int i = 0; i < numBranches; i++) {
		next[i] = NULL;
	}
}
linkedNode::~linkedNode()
{
	delete prev;
	delete [] next;
}
void linkedNode::set_branches(int numBranches)
{
	branches = numBranches;
}
int linkedNode::get_branches()
{
	return branches;
}