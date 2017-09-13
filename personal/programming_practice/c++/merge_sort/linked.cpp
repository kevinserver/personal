#include "linked.h"

linked::linked()
{
	prev = NULL;
	next = NULL;
	sortElementA = 0;
	sortElementB = 0;
}
linked::~linked()
{

}
void linked::setA(int a)
{
	sortElementA = a;
}
int linked::getA()
{
	return sortElementA;
}
void linked::setB(double b)
{
	sortElementB = b;
}
double linked::getB()
{
	return sortElementB;
}