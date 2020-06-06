#ifndef _CONVERSATION_H_
#define _CONVERSATION_H_

#include "ObjectInterface.h"
#include <iostream>
#include <chrono>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <exception>
using namespace std;
enum BOOL { TRUE, FALSE };

class GoBack : public exception {
public:
	const char* what() {
		return "GoBack";///?????
	}
};

enum ConversationStatus { READ, UNREAD };

typedef chrono::system_clock::time_point SysTime;

// ------------------------------- Message ------------------------------- //
class Message {
public:
	Message(const string& by, const string& content) : by_(by), content_(content) {}
	void Print() const { cout << by_ << " : " << content_ << endl; }
private:
	string by_;
	string content_;
};


// ------------------------------- Conversation ------------------------------- //

class Conversation : public ObjectInterface {

public:
	void Preview(string activeUsrName);
	void VrtDo(string cmd, string activeUsrName);
	void Help() const;
	bool IsRead(string name);
	SysTime getTime() { return time_; };
	void DisplayParticipants() const;
	void  addParticipant(string name);
	void removeParticipant(string name);
	void updateTime();
	//void markAsRead(string name);
	Conversation() : time_(chrono::system_clock::now()) {};




private:
	set<string> users_;
	vector<Message> messages_;
	map<string, ConversationStatus> readStatus_;
	SysTime time_;
	
};


#endif
