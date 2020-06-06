#ifndef _TEACH_H_
#define _TEACH_H_
#include "Person.H"
#include <string>
#include <iostream>

using namespace std;

class Teacher : public Person{
public:
	Teacher();
	Teacher(string name, unsigned age, unsigned seniority);
	unsigned getSeniority() const;
	void print() const;
private:
	unsigned seniority_;
};

#endif
