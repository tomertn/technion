#include <iostream>
#include <exception>
#include <string>
#include "ChatNet.h"
#include "MySharedPtr.h"
using namespace std;



int main() {
	/*
	MySharedPtr<int> p1(new int); // p1 counter=1
	*p1 = 0; // the value pointed to by p1 is changed to 0
	cout << (*p1) << endl; // prints the value pointed to by p1 (prints 0)
	cout << (*(p1.get())) << endl; // same as previous line
	cout << ((p1.getCnt())) << endl;
	MySharedPtr<int> p2(p1); // p1/p2 counter=2
	MySharedPtr<int> p3(new int); // p3 counter =1
	p3 = p1; // p3/p2/p1 counter=3, previous p3 object deleted
	MySharedPtr<int> p4(new int); // p4 counter =1
	p2 = p4; // p2/p4 counter = 2, p1/p3 counter = 2, no object is deleted
	p1 = p2; // p1/p2/p4 counter =3, p3 counter = 1, no object is deleted
	return 0;
}
	*/
	string line;
	ChatNet MamatChat("MamatChat", "Admin", "1234");
	while (!cin.eof())
	{
		try
		{
			getline(cin, line);
			MamatChat.Do(line);
		}
		catch (BackSignal&) // Exit
		{
			break;
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "Unexpected Error" << endl;
			return 1;
		}
	}

	return 0;
};

