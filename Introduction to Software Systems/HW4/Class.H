#ifndef _CLASS_H_
#define _CLASS_H_

#include <string>
#include <iostream>
#include <vector>
#include "defs.H"
#include "Room.H"
#include "Child.H"
#include "Teacher.H"

using std::string;
using std::vector;

class Class : public Room{
public:
	Class();
	Class(unsigned num, unsigned size, double ratio, unsigned classAge, unsigned maxOfChildren);


	unsigned getTeachersNum() const;
	unsigned getClassAge() const;
	double getRatio() const;
	string getAChildPhone(string name) const;

	void addTeacher(Teacher teacher);
	Result addChild(Child child);
	Result removeTeacher(string name);
	Result removeChild(string name);
	Result setChildAsSick(string name);

	void print() const;

private:
	double ratio_;
	unsigned classAge_;
	unsigned maxChildren_;
	vector<Child> childrenVec_;
	vector<Teacher> TeachersVec_;
};

#endif
