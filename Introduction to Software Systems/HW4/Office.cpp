#include "Office.H"
#include "defs.H"
#include <iostream>

using namespace std;

Office::Office() :Room(1, 20), isBusy_(false), sickChild_("NONE") { this->occupiedOn(); };

Result Office::addClass(unsigned size, double ratio, unsigned classAge, unsigned maxOfChildren) {
	if (isBusy_) { return FAILURE; }
	int len = this->classVec_.size(), i;
	for ( i = 0; i < len; i++)
	{
		if (classAge == classVec_[i].getClassAge())
		{
			return FAILURE;
		}
	}
	Class a(classVec_.size()+2, size, ratio, classAge, maxOfChildren) ;
	this->classVec_.push_back(a);
	return SUCCESS;
}

Result Office::addChildOffice(Child child) {
	if (isBusy_) { return FAILURE; }
	int len = this->classVec_.size(), i;
	for (i = 0; i < len; i++)
	{
		if (child.getAge() == classVec_[i].getClassAge())
		{
			return classVec_[i].addChild(child);
		}
	}
	return FAILURE;
}
Result Office::addTeacherOffice(Teacher teacher) {
	if (isBusy_) { return FAILURE; }
	int len = this->classVec_.size(), i;
	for (i = 0; i < len; i++)
	{
		if (classVec_[i].isRoomOccupied() == false)
		{
			classVec_[i].addTeacher(teacher);
			return SUCCESS;
		}
	}
	if (len == 0) { return FAILURE; }
	i = 0;
	double maxRatio = classVec_[i].getRatio();
	int maxI = 0;
	for (i = 1; i < len; i++)
	{
		if (classVec_[i].getRatio() > maxRatio)
		{
			maxRatio = classVec_[i].getRatio();
			maxI = i;
		}
	}
	 classVec_[maxI].addTeacher(teacher);
	 return SUCCESS;
}
Result Office::removeTeacherOffice(string name) {
	if (isBusy_) { return FAILURE; }
	int len = this->classVec_.size(), i;
	for (i = 0; i < len; i++)
	{
		if (classVec_[i].removeTeacher(name) == SUCCESS)
		{
			return SUCCESS;
		}
	}
	return FAILURE;
}
Result Office::removeChildOffice(string name) {
	if ((isBusy_)&&(this->sickChild_.compare(name)!=0)) { return FAILURE; }
	int len = this->classVec_.size(), i;
	for (i = 0; i < len; i++)
	{
		if (classVec_[i].removeChild(name) == SUCCESS)
		{
			if (this->sickChild_.compare(name) == 0){
				isBusy_ = false;
			}
			return SUCCESS;
		}
	}
	return FAILURE;
}
Result Office::removeClass(unsigned classAge) {
	if (isBusy_) { return FAILURE; }
	int len = this->classVec_.size(), i;
	for (i = 0; i < len; i++)
	{
		if (classVec_[i].getClassAge() == classAge)
		{
			this->classVec_.erase(classVec_.begin() + i);
			return SUCCESS;
		}
	}
	return FAILURE;
}


Result Office::sickChildMark(string name) {
	if (isBusy_) { return FAILURE; }
	int len = this->classVec_.size(), i;
	string s;
	for (i = 0; i < len; i++)
	{
		s = classVec_[i].getAChildPhone(name);
		if (s.compare("No Child" )!= 0)
		{
			if (s.length() != 10) { return FAILURE; }
			if ((s[0] != '0') || (s[1] != '5')) { return FAILURE; }
			cout << "Reporting sick child : " << endl;
			cout << "Name : " << name << endl;
			cout << "Parent's phone number : " << s << endl;
			isBusy_ = true;
			sickChild_ = name;
			classVec_[i].setChildAsSick(name);
			return SUCCESS;
		}
	}
	return FAILURE;
}
void Office::print() const {
	cout << "Printing office status :" << endl;
	cout << "========================" << endl;
	cout << "Number : 1" << endl;
	cout << "Size : 20 square meters " << endl;
	cout << "Is Occupied : true" << endl;
	string t = "false";
	if (isBusy_) { t = "true"; }
	cout << "Office is busy : " <<t << endl;
	if (isBusy_) {
		cout << "Sick child : " << sickChild_ << endl;
	}
	cout << endl;
	int len = this->classVec_.size(), i;
	for (i = 0; i < len; i++)
	{
		classVec_[i].print();
	}
}

