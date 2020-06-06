#include "Child.H"

using namespace std;


Child::Child() : phoneNum_(""), isSick_(false) {};
Child::Child(string name, unsigned age, string phoneNum) :
	Person(name, age), phoneNum_(phoneNum),isSick_(false) {};

string Child::getPhoneNum() const
{
	return this->phoneNum_;
}

void Child::setPhoneNum(string phoneNum)
{
	this->phoneNum_ = phoneNum;
}
Result Child::setSick()
{
	if (!this->isSick_)
	{
		this->isSick_ = true; return SUCCESS;
	}
	return FAILURE;
}
void Child::print() const
{
	string t = "false";
	Person::print();
	if (isSick_) {
		t = "true";
	}
	cout << "Parant's Phone : " << phoneNum_ << endl;
	cout << "Is sick : " << t;
	cout << endl;
}

