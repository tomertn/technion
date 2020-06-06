#ifndef _MESSAGEBOX_H_
#define _MESSAGEBOX_H_

#include "ObjectInterface.h"
#include "Conversation.h"
#include <list>
#include "MySharedPtr.h"

class makeNewConversation{ //: public exception {
public:
	vector<string> namesOfMembers;
	//const char* what() {};
	void addMemberToVecotr(string member) {
		namesOfMembers.push_back(member);
	}
};

class OpenAConversation{ //: public exception {
private:
	MySharedPtr<Conversation> convers_;
public:
	//const char* what() {};
	OpenAConversation(MySharedPtr<Conversation> convers) : convers_(convers) {};
	MySharedPtr<Conversation> getPtr() const { return convers_; }
};

/*
class DeleteConsFromBox : public exception {
private:
	MySharedPtr<Conversation> convers_;
public:
	const char* what() {};
	DeleteConsFromBox(MySharedPtr<Conversation> convers) : convers_(convers) {};
	MySharedPtr<Conversation> getPtr() const { return convers_; }
};
*/

class SearchName {//: public exception {
private:
	string name_;
public:
	//const char* what() {};
	SearchName(string name) : name_(name) {};
	string getPtr() const { return name_; }
};




class MessageBox : public ObjectInterface {

public:
	void Preview(string activeUsrName);
	void VrtDo(string cmd, string activeUsrName);
	void Help() const;
	int getSize() const;
	string getNameOfUser() const { return nameOfUser; }
	void addConversations(MySharedPtr<Conversation> conversation) { listOfPConversations.push_back(conversation); }
	//void removeConversations(MySharedPtr<Conversation> conversation);
	list<MySharedPtr<Conversation>>& getList() { return listOfPConversations; }
	//c'tors
	MessageBox() :nameOfUser(NULL) {};
	MessageBox(string name) : nameOfUser(name) {};
	//~MessageBox();



	
private:
	string nameOfUser;
	list<MySharedPtr<Conversation>> listOfPConversations;
	

};


#endif
