#ifndef _USER_H_
#define _USER_H_

#include "ObjectInterface.h"
#include "MessageBox.h"

class OpenAMessages {//: public exception {
private:
	MySharedPtr<MessageBox> Messages_;
public:
	//const char* what() {};
	OpenAMessages(MySharedPtr<MessageBox> Messages) : Messages_(Messages) {};
	MySharedPtr<MessageBox> getPtr() const { return Messages_; }
};

class LogOut {//: public exception {
public:
	//const char* what() {}
  
};


class NewAdmin{// : public exception {
private:
	string name_;
	string pass_;
public:
	//const char* what() {};
	NewAdmin(string name, string pass) : name_(name) , pass_(pass){};
	string getName() const { return name_; }
	string getPass() const { return pass_; }
};

class DeleteUser {//: public exception {
private:
	string name_;
	
public:
	//const char* what() {};
	DeleteUser(string name) : name_(name) {};
	string getName() const { return name_; }
};

	// ------------------------------- User ------------------------------- //
	class User : public ObjectInterface {
	protected:
		string name_;
		string password_;
		MySharedPtr<MessageBox> pMessageBox_;
		int type_;//zero for user 1 for admin
		
	public:
		void Preview(string activeUsrName);
		void VrtDo(string cmd, string activeUsrName);
		void Help() const;
		string getName() const { return name_; }
		string getPassword() const { return password_; }
		MySharedPtr<MessageBox> getMessageBox() const { return pMessageBox_; }
		int getType() const{ return type_; }

		//c'tors
		User() :name_(NULL), password_(NULL), pMessageBox_(new MessageBox()), type_(0) { };
		User(string userName, string password) :name_(userName), password_(password), pMessageBox_(new MessageBox(userName)), type_(0) {};
		//User(const User& userToCopy) : name_(userToCopy.getName()), password_(userToCopy.getPassword()), messageBox_(userToCopy.getMessageBox()) {};
	
};
// ------------------------------- Admin ------------------------------- //
	class Admin : public User {
	public:
		void VrtDo(string cmd, string activeUsrName);
		void Help() const;
		Admin(string userName, string password) : User(userName, password) { type_ = 1; };
	};
#endif

