#ifndef _OFFICE_H_
#define _OFFICE_H_

#include <string>
#include <vector>

#include "Room.H"
#include "defs.H"
#include "Class.H"

using std::string;
using std::vector;

class Office : public Room {
public:
	Office();
	Result addClass(unsigned size, double ratio, unsigned classAge, unsigned maxOfChildren);
	Result addChildOffice(Child child);
	Result addTeacherOffice(Teacher teacher);
	Result removeTeacherOffice(string name);
	Result removeChildOffice(string name);
	Result removeClass(unsigned classAge);
	Result sickChildMark(string name);
	void print() const;
private:
	bool isBusy_;
	string sickChild_;
	vector<Class> classVec_;
};

#endif
