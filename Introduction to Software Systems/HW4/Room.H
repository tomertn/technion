#ifndef _ROOM_H_
#define _ROOM_H_

#include <string>
#include <iostream>
#include "defs.H"

using namespace std;

class Room {
public:
	Room();
	Room(unsigned num, unsigned size);
	unsigned getNumOfRoom() const;
	bool isRoomOccupied() const;
	Result occupiedOn();
	Result occupiedOff();
	void print() const;
protected:
	unsigned num_;
	unsigned size_;
	bool isOccupied_;
};

#endif
