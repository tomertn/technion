#include "Room.H"
#include "defs.H"
#include <iostream>

using namespace std;


Room::Room() : num_(0), size_(0), isOccupied_(false) {};
Room::Room(unsigned num, unsigned size) :
	num_(num), size_(size), isOccupied_(false) {};

unsigned Room::getNumOfRoom() const {
	return this->num_;
}
bool Room::isRoomOccupied() const {
	return this->isOccupied_;
}
Result Room::occupiedOn() {
	if (this->isOccupied_)
		return FAILURE;
	this->isOccupied_ = true;
	return SUCCESS;
}
Result Room::occupiedOff() {
	if (!this->isOccupied_)
		return FAILURE;
	this->isOccupied_ = false;
	return SUCCESS;
}
void Room::print() const {
	cout << "Number : " << this->num_ << endl;
	cout << "Size : " << this->size_<< " square meters " << endl;
	string t = "false";
	if (isOccupied_) {
		t = "true";
	}
	cout << "Is Occupied : " << t << endl;
	}
