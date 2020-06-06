#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include <iostream>

using namespace std;
//using std::string;

class Person {

public:
	Person();
	Person(string name, unsigned int age);
	unsigned getAge() const;
	string getName() const;
	virtual ~Person();
	void print() const;

protected :
	string name_;
	unsigned int age_;

};

#endif
