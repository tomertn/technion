#include "Class.H"
#include "defs.H"
#include <iostream>

using namespace std;

Class::Class() : ratio_(0),classAge_(0), maxChildren_(0) {};
Class::Class(unsigned num, unsigned size, double ratio, unsigned classAge, unsigned maxOfChildren) :
	Room(num, size), ratio_(ratio), classAge_(classAge),
	maxChildren_(maxOfChildren){};

unsigned Class::getTeachersNum() const {
	return this->TeachersVec_.size();
}

unsigned Class::getClassAge() const {
	return this->classAge_;
}
double Class::getRatio() const {
	if(TeachersVec_.size()==0){ return FAILURE; }
	return (childrenVec_.size()/(double)TeachersVec_.size());
}
string Class::getAChildPhone(string name) const {
	int len = childrenVec_.size(),i;
	for (i = 0; i < len; i++)
	{
		if (name == childrenVec_[i].getName()) 
			return childrenVec_[i].getPhoneNum();
	}
	return "No Child";
}

void Class::addTeacher(Teacher teacher) {
	TeachersVec_.push_back(teacher);
	this->occupiedOn();
}

Result Class::addChild(Child child) {
	if (child.getAge() != this->classAge_) return FAILURE;
	if (this->childrenVec_.size()>=this->maxChildren_) return FAILURE;
	if (((this->childrenVec_.size()+1)/(double)(this->TeachersVec_.size())) > this->ratio_) return FAILURE;
	childrenVec_.push_back(child);
	return SUCCESS;
}

Result Class::removeTeacher(string name) {  //should check again
	if (TeachersVec_.size() == 0) return FAILURE;
	if (TeachersVec_.size() == 1) {
		if (childrenVec_.size() != 0) return FAILURE;
		if (TeachersVec_[0].getName() == name) {
			TeachersVec_.erase(TeachersVec_.begin());
			this->occupiedOff();
			return SUCCESS;
		}
		return FAILURE;
	}

	if (((this->childrenVec_.size()) / (double)(this->TeachersVec_.size() - 1)) > this->ratio_)
		return FAILURE;
	int len = TeachersVec_.size(), i;
	for (i = 0; i < len; i++)
	{
		if (name == TeachersVec_[i].getName())
		{
			this->TeachersVec_.erase(TeachersVec_.begin() + i);
			return SUCCESS;
		}
	}
	return FAILURE;
}


Result Class::removeChild(string name) { //should check again
	if (TeachersVec_.size() == 0) return FAILURE;
	if (((this->childrenVec_.size() - 1) / (double)(this->TeachersVec_.size())) > this->ratio_)
		return FAILURE;
	int len = childrenVec_.size(), i;
	for (i = 0; i < len; i++)
	{
		if (name == childrenVec_[i].getName())
		{
			this->childrenVec_.erase(childrenVec_.begin() + i);
			return SUCCESS;
		}
	}
	return FAILURE;
}

Result Class::setChildAsSick(string name) {
	int len = childrenVec_.size(), i;
	for (i = 0; i < len; i++)
	{
		if (name == childrenVec_[i].getName())
		{
			return this->childrenVec_[i].setSick();
		}
	}
	return FAILURE;
}

void Class::print() const {
	int i, len;
	cout << "Printing class status :" << endl;
	cout << "========================" << endl;
	Room::print();
	cout << "Max number of children : " << maxChildren_ << endl;
	cout << "Number of children : " << childrenVec_.size() << endl;
	cout << "Number of teachers : " << TeachersVec_.size() << endl;
	cout << "Max value for ratio : " << ratio_ << endl;
	if(TeachersVec_.size()==0)
		cout << "Current ratio : 0" << endl;
	else
	cout << "Current ratio : " << (this->childrenVec_.size()) / (double)(this->TeachersVec_.size()) << endl;
	cout << "Children age range : " << classAge_ << " - " << (classAge_ + 1) << endl;
	cout << endl;
	if (childrenVec_.size() > 0) {
		cout << "Printing childrens status :" << endl;
		cout << "========================" << endl;
		len = childrenVec_.size();
		for (i = 0; i < len; i++) {
			childrenVec_[i].print();
		}
		cout << endl;
	}
	if (TeachersVec_.size() > 0) {
		cout << "Printing teachers status :" << endl;
		cout << "========================" << endl;
		len = TeachersVec_.size();
		for (i = 0; i < len; i++) {
			TeachersVec_[i].print();
		}
		cout << endl;
	}
}

	
