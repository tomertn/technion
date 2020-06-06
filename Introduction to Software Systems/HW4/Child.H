#ifndef _CHILD_H_
#define _CHILD_H_
#include "Person.H"
#include "defs.H"
#include <string>
#include <iostream>

using namespace std;

class Child : public Person {
public:
	Child();
	Child(string, unsigned, string);
	string getPhoneNum() const;
	void setPhoneNum(string);
	Result setSick();
	void print() const;

private:
	string phoneNum_;
	bool isSick_;
};

#endif
