#include "LinkedList.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	LinkedList<int> power2;
	int val = 2;
	for (int i = 0; i < 10; i++)
	{
		power2.AddTail(val);
		val *= 2;
	}
	cout << "Initial list: " << endl;
	power2.PrintForward();
	cout << "Printing recursively forward from 64: " << endl;
	LinkedList<int>::Node* node = power2.Find(64);
	power2.PrintForwardRecursive(node);

	cout << "Printing recursively in reverse from 512: " << endl;
	node = power2.Find(512);
	power2.PrintReverseRecursive(node);

	return 0;
}