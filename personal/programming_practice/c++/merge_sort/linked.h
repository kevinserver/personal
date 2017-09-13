#include <stdio>
#include <stdlib>

class linked
{
public:
	linked();
	~linked();
	void setA(int);
	int getA();
	void setB(double);
	double getB();
	linked * prev;
	linked * next;
private:
	int sortElementA;
	double sortElementB;
};