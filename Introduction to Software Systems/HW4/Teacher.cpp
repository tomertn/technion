#include "Teacher.H"

using namespace std;

Teacher::Teacher() : seniority_(0) {};
Teacher::Teacher(string name, unsigned age, unsigned seniority) :
	Person(name, age), seniority_(seniority) {};

unsigned Teacher::getSeniority() const {
	return this->seniority_;
}
void Teacher::print() const {
	Person::print();
	cout << "Seniority : " << this->seniority_ << endl;
}