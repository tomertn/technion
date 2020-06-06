#include "Person.H"

using std::string;
using std::cout;
using std::endl;

Person::Person() : name_(""), age_(0) {};
Person::Person(string name, unsigned int age) : name_(name), age_(age) {};

unsigned int Person::getAge() const
{
	return this->age_;
}

string Person::getName() const
{
	return this->name_;
}

Person::~Person() {};
void Person::print() const
{
	cout << "Name : " << name_ << endl;
	cout << "Age : " << age_ << endl;
}
