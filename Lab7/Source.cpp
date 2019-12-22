#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>
using namespace std;

int main()
{
	cout << "Here we go\n";

	testAll();
	cout << "Short done\n";

	testAllExtended();
	cout << "Extended done\n";


	system("pause");
	return 0;
}