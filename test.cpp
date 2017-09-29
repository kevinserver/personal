#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	string s = "(3,45)";
	stringstream ss;
	ss << s;
	char c;
	int real, imag;
	ss >> c >> real >> c >>imag >> c;
	cout << real << " " << imag << endl;
}





// ss = s;
// ss >> c >> real >> c >>imag >> c;